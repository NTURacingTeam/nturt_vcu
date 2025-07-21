#include "vcu/dashboard.h"

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/msg.h>
#include <nturt/sys/sys.h>

// project includes
#include "vcu/ctrl/states.h"

LOG_MODULE_REGISTER(vcu_peripherals);

/* type ----------------------------------------------------------------------*/
struct peripherials_ctx {
  int rtd_sound_count;
  struct k_work_delayable rtd_blink_dwork;
  struct k_work_delayable rtd_sound_dwork;
};

/* static function declaration -----------------------------------------------*/
static int gpio_init();

static void msg_cb(const struct zbus_channel *chan);
static void input_cb(struct input_event *evt, void *user_data);
static void states_cb(enum states_state state, bool is_entry, void *user_data);
static void rtd_blink_work(struct k_work *work);
static void rtd_sound_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static const struct gpio_dt_spec buzzer =
    GPIO_DT_SPEC_GET(DT_CHOSEN(nturt_buzzer), gpios);
static const struct gpio_dt_spec rtd_light =
    GPIO_DT_SPEC_GET(DT_CHOSEN(nturt_rtd_light), gpios);
static const struct gpio_dt_spec brake_light =
    GPIO_DT_SPEC_GET(DT_CHOSEN(nturt_brake_light), gpios);

static struct peripherials_ctx g_ctx = {
    .rtd_sound_count = 0,
    .rtd_blink_dwork = Z_WORK_DELAYABLE_INITIALIZER(rtd_blink_work),
    .rtd_sound_dwork = Z_WORK_DELAYABLE_INITIALIZER(rtd_sound_work),
};

// use the same init priority as the LEDs since they are used in the same way
SYS_INIT(gpio_init, POST_KERNEL, CONFIG_LED_INIT_PRIORITY);

ZBUS_LISTENER_DEFINE(peripherials_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_sensor_cockpit_chan, peripherials_listener, 0);

INPUT_CALLBACK_DEFINE(NULL, input_cb, NULL);

STATES_CALLBACK_DEFINE(STATE_RTD_BLINK | STATE_RTD_STEADY | STATE_RTD_SOUND,
                       states_cb, &g_ctx);

/* static function definition ------------------------------------------------*/
static int gpio_init() {
  const struct gpio_dt_spec *gpios[] = {
      &buzzer,
      &rtd_light,
      &brake_light,
  };

  for (int i = 0; i < ARRAY_SIZE(gpios); i++) {
    if (!device_is_ready(gpios[i]->port)) {
      LOG_ERR("Device %s not ready", gpios[i]->port->name);
      return -ENODEV;
    }
  }

  int ret;
  for (int i = 0; i < ARRAY_SIZE(gpios); i++) {
    ret = gpio_pin_configure_dt(gpios[i], GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
      LOG_ERR("Failed to configure GPIO %s pin %hu: %s", gpios[i]->port->name,
              gpios[i]->pin, strerror(-ret));
      return ret;
    }
  }

  return 0;
}

static void msg_cb(const struct zbus_channel *chan) {
  const struct msg_sensor_cockpit *msg = zbus_chan_const_msg(chan);

  gpio_pin_set_dt(&brake_light, msg->brake > 0);
}

static void input_cb(struct input_event *evt, void *user_data) {
  if (evt->type == INPUT_EV_KEY && evt->value) {
    switch (evt->code) {
      case INPUT_BTN_RTD:
        if (states_valid_transition(TRANS_CMD_RTD)) {
          states_transition(TRANS_CMD_RTD);
        }
        break;

      case INPUT_BTN_DISABLE:
        if (states_valid_transition(TRANS_CMD_DISABLE)) {
          states_transition(TRANS_CMD_DISABLE);
        }
        break;

      case INPUT_BTN_RESET:
        sys_reset();
        break;
    }
  }
}

static void states_cb(enum states_state state, bool is_entry, void *user_data) {
  struct peripherials_ctx *ctx = user_data;

  switch (state) {
    case STATE_RTD_BLINK:
      if (is_entry) {
        k_work_schedule(&ctx->rtd_blink_dwork, K_NO_WAIT);
      } else {
        k_work_cancel_delayable(&ctx->rtd_blink_dwork);
        gpio_pin_set_dt(&rtd_light, false);
      }

      break;

    case STATE_RTD_STEADY:
      gpio_pin_set_dt(&rtd_light, is_entry);

      break;

    case STATE_RTD_SOUND:
      if (is_entry) {
        ctx->rtd_sound_count = 0;
        k_work_schedule(&ctx->rtd_sound_dwork, K_NO_WAIT);
      } else {
        gpio_pin_set_dt(&buzzer, false);
        k_work_cancel_delayable(&ctx->rtd_sound_dwork);
      }

      break;

    default:
      break;
  }
}

static void rtd_blink_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct peripherials_ctx *ctx =
      CONTAINER_OF(dwork, struct peripherials_ctx, rtd_blink_dwork);

  gpio_pin_toggle_dt(&rtd_light);

  k_work_reschedule(&ctx->rtd_blink_dwork, LED_BLINK_PERIOD);
}

static void rtd_sound_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct peripherials_ctx *ctx =
      CONTAINER_OF(dwork, struct peripherials_ctx, rtd_sound_dwork);

  if (ctx->rtd_sound_count % 2 == 0) {
    gpio_pin_set_dt(&buzzer, true);

    if (ctx->rtd_sound_count == 0) {
      k_work_reschedule(&ctx->rtd_sound_dwork, K_MSEC(1000));
    } else {
      k_work_reschedule(&ctx->rtd_sound_dwork, K_MSEC(200));
    }

  } else {
    gpio_pin_set_dt(&buzzer, false);

    if (ctx->rtd_sound_count >= 5) {
      states_transition(TRANS_CMD_RTD_FINISH);
    } else {
      k_work_reschedule(&ctx->rtd_sound_dwork, K_MSEC(100));
    }
  }

  ctx->rtd_sound_count++;
}

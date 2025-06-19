// glibc includes
#include <stdbool.h>
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

// project includes
#include "vcu/ctrl/states.h"

LOG_MODULE_REGISTER(rtd_sound);

/* type ----------------------------------------------------------------------*/
/// @brief RTD sound module context.
struct rtd_sound_ctx {
  int count;

  struct k_work_delayable dwork;
};

/* static function declaration -----------------------------------------------*/
/// @brief States handler when entering or exiting RTS sound state.
static void rtd_sound_rtd_sound_handler(enum states_state state, bool is_entry,
                                        void *user_data);

/// @brief Work to play the RTD sound and transition to running state when the
/// sound finishes.
static void update_work(struct k_work *work);

static int init();

/* static variable -----------------------------------------------------------*/
static const struct gpio_dt_spec buzzer =
    GPIO_DT_SPEC_GET(DT_CHOSEN(nturt_buzzer), gpios);

/// @brief State module context.
static struct rtd_sound_ctx g_ctx = {
    .count = 0,
    .dwork = Z_WORK_DELAYABLE_INITIALIZER(update_work),
};

STATES_CALLBACK_DEFINE(STATE_RTD_SOUND, rtd_sound_rtd_sound_handler, &g_ctx);

SYS_INIT(init, APPLICATION, CONFIG_VCU_STATES_INIT_PRIORITY);

/* static function definition ------------------------------------------------*/
static void rtd_sound_rtd_sound_handler(enum states_state state, bool is_entry,
                                        void *user_data) {
  (void)state;

  struct rtd_sound_ctx *rtd_sound = user_data;

  if (is_entry) {
    rtd_sound->count = 0;
    k_work_schedule(&rtd_sound->dwork, K_NO_WAIT);
  } else {
    gpio_pin_set_dt(&buzzer, false);
    k_work_cancel_delayable(&rtd_sound->dwork);
  }
}

static void update_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct rtd_sound_ctx *rtd_sound =
      CONTAINER_OF(dwork, struct rtd_sound_ctx, dwork);

  if (rtd_sound->count % 2 == 0) {
    gpio_pin_set_dt(&buzzer, true);

    if (rtd_sound->count == 0) {
      k_work_reschedule(&rtd_sound->dwork, K_MSEC(1000));
    } else {
      k_work_reschedule(&rtd_sound->dwork, K_MSEC(200));
    }

  } else {
    gpio_pin_set_dt(&buzzer, false);

    if (rtd_sound->count >= 5) {
      states_transition(TRANS_CMD_RTD_FINISH);
    } else {
      k_work_reschedule(&rtd_sound->dwork, K_MSEC(100));
    }
  }

  rtd_sound->count++;
}

static int init() {
  if (!device_is_ready(buzzer.port)) {
    LOG_ERR("Buzzer device not ready");
    return -ENODEV;
  }

  int ret = gpio_pin_configure_dt(&buzzer, GPIO_OUTPUT_INACTIVE);
  if (ret < 0) {
    LOG_ERR("Failed to configure buzzer: %s", strerror(-ret));
    return ret;
  }

  return 0;
}

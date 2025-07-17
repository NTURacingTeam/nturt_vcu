#include "vcu/dashboard.h"
#include <zephyr/drivers/input/sensor_axis.h>
#include <nturt/msg/msg.h>

// glibc incldes
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>
#include <zephyr/drivers/led_strip.h>

/* type ----------------------------------------------------------------------*/
enum {
  ACTIVE,
  INCREASING,

  NUM_STATES,
};

enum {
  BRIGHTNESS_SET,

  APPS_SET,

  BSE_SET,

  NUM_MODE,
};

#define DEFAULT_MODE BRIGHTNESS_SET

struct dashboard_setting_ctx {
  struct k_spinlock lock;
  
  bool states[NUM_STATES];
  uint8_t mode;

  bool blink_state;

  struct k_work_delayable modify_dwork;
  struct k_work_delayable blink_dwork;

  struct led_rgb blink_rgb[LED_STRIP_LEN];
};

/* static function declaration -----------------------------------------------*/
static int init();

static void switch_mode();
static uint8_t get_mode();
static void set_mode(uint8_t mode);

static void rgb_set_level(struct led_rgb *rgb, int len, int level);
static void rgb_blink_set(struct led_rgb *rgb, int len, bool set);
static void speed_blink(bool set);

static void show_brightness(uint8_t brightness);
static void clear_display();

static void modify_brightness(bool increase);

static void blink_work(struct k_work *work);
static void modify_work(struct k_work *work);

static void input_cb(struct input_event *evt, void *user_data);
static void msg_cb(const struct zbus_channel *chan);

/* static variable -----------------------------------------------------------*/
static const struct device *speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));
static const struct device *accel_display =
    DEVICE_DT_GET(DT_NODELABEL(accel_display));
static const struct device *brake_display =
    DEVICE_DT_GET(DT_NODELABEL(brake_display));

static const struct device *apps1 = 
    DEVICE_DT_GET(DT_NODELABEL(apps1_sensor_axis));
static const struct device *apps2 = 
    DEVICE_DT_GET(DT_NODELABEL(apps2_sensor_axis));

static const struct device *bse1 =
    DEVICE_DT_GET(DT_NODELABEL(bse1_sensor_axis));
static const struct device *bse2 = 
    DEVICE_DT_GET(DT_NODELABEL(bse2_sensor_axis));


static struct dashboard_setting_ctx g_ctx = {
    .states = {0},
    .blink_state = 1,
    .mode = DEFAULT_MODE,
    .modify_dwork = Z_WORK_DELAYABLE_INITIALIZER(modify_work),
    .blink_dwork = Z_WORK_DELAYABLE_INITIALIZER(blink_work),
};

SYS_INIT(init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

ZBUS_LISTENER_DEFINE(dashboard_settings_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_cockpit_data_chan, dashboard_settings_listener, 0);

/* function definition -------------------------------------------------------*/
void dashboard_setting_start() {
  g_ctx.states[ACTIVE] = true;
  k_work_schedule(&g_ctx.blink_dwork, K_NO_WAIT);
}

void dashboard_setting_stop() {
  g_ctx.states[ACTIVE] = false;
  k_work_cancel_delayable(&g_ctx.blink_dwork);
}

/* static function definition ------------------------------------------------*/
static void speed_blink(bool set) {
  if(set){
    int brightness = dashboard_brightness_get();
    show_brightness(brightness);
  }else{
    clear_display();
  }
}

static int init() {
  for(int i=0; i<LED_STRIP_LEN; i++) {
    g_ctx.blink_rgb[i].r = 0;
  }
  return 0;
}

static void rgb_set_level(struct led_rgb *rgb, int len, int level) {
  level = DIV_ROUND_CLOSEST(level * len, 100);

  for (int i = 0; i < level; i++) {
    rgb[i].r = 1;
  }

  for (int i = level; i < len; i++) {
    rgb[i].r = 0;
  }
}

static void rgb_blink_set(struct led_rgb *rgb, int len, bool set) {
  rgb[0].r = set;
  rgb[len-1].r = set;
}

static void clear_display() {
  static const char* empty_str = "  ";
  auxdisplay_write(speed_display, empty_str, strlen(empty_str));
}

static void show_brightness(uint8_t brightness) {
  // longer to prevent compiler warnings
  char buf[20];
  snprintf(buf, sizeof(buf), "%2hu", CLAMP(brightness, 0, 99));
  auxdisplay_write(speed_display, buf, strlen(buf));
}

static void modify_brightness(bool increase) {
  int brightness = dashboard_brightness_get();
  brightness += increase ? 1 : -1;
  brightness = CLAMP(brightness, 0, 100);

  dashboard_brightness_set(brightness);
  if (IS_ENABLED(CONFIG_VCU_DASHBOARD_SETTINGS)) {
    dashboard_settings_save();
  }

  show_brightness(brightness);
}

static uint8_t get_mode() {
  return g_ctx.mode;
}

static void set_mode(uint8_t mode) {
  k_spinlock_key_t key = k_spin_lock(&g_ctx.lock);
  g_ctx.mode = mode;
  k_spin_unlock(&g_ctx.lock, key);
}

static void switch_mode() {
  uint8_t next_mode = (get_mode() + 1) % NUM_MODE;
  set_mode(next_mode);
  if(next_mode != BRIGHTNESS_SET) {
    int brightness = dashboard_brightness_get();
    show_brightness(brightness);
  }
}

static void msg_cb(const struct zbus_channel *chan) {
  k_spinlock_key_t key = k_spin_lock(&g_ctx.lock);
  if(!g_ctx.states[ACTIVE]) {
    k_spin_unlock(&g_ctx.lock, key);
    return;
  }
  
  struct led_rgb rgb[LED_STRIP_LEN];

  if(chan == &msg_cockpit_data_chan) {
    const struct msg_cockpit_data *msg = zbus_chan_const_msg(chan);

    rgb_set_level(rgb, ARRAY_SIZE(rgb), msg->accel);
    led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);

    rgb_set_level(rgb, ARRAY_SIZE(rgb), msg->brake);
    led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);
  }
  k_spin_unlock(&g_ctx.lock, key);
}

static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_setting_ctx *ctx = user_data;

  if (!ctx->states[ACTIVE] || evt->type != INPUT_EV_KEY) {
    return;
  }

  // Switch States
  if(evt->value){
    switch (evt->code) {
      case INPUT_BTN_LEFT:
        switch_mode();
        break;

      default:
        break;
    }
  }

  // Set Dashboard Brightness
  if (evt->value && ctx->mode == BRIGHTNESS_SET) {
    switch (evt->code) {
      case INPUT_BTN_UP :
        modify_brightness(true);
        break;

      case INPUT_BTN_DOWN:
        modify_brightness(false);
        break;

      case INPUT_BTN_UP_HOLD:
        ctx->states[INCREASING] = true;
        k_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
        break;

      case INPUT_BTN_DOWN_HOLD:
        ctx->states[INCREASING] = false;
        k_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
        break;

      default:
        break;
    }

  } else if (evt->code == INPUT_BTN_UP_HOLD ||
             evt->code == INPUT_BTN_DOWN_HOLD) {
    k_work_cancel_delayable(&ctx->modify_dwork);
  }

  // Set APPS Config
  if (evt->value && ctx->mode == APPS_SET) {
    switch(evt->code) {
      case INPUT_BTN_UP:
        sensor_axis_sensor_max_set_curr(apps1, 10, K_MSEC(10));
        sensor_axis_sensor_max_set_curr(apps2, 10, K_MSEC(10));
        break;
      
      case INPUT_BTN_DOWN:
        sensor_axis_sensor_min_set_curr(apps1, 10, K_MSEC(10));
        sensor_axis_sensor_min_set_curr(apps2, 10, K_MSEC(10));
        break;
      
      default:
        break;
    }
  }

  // Set Brake Config
  if (evt->value && ctx->mode == BSE_SET) {
    switch(evt->code) {
      case INPUT_BTN_UP:
        sensor_axis_sensor_max_set_curr(bse1, 10, K_MSEC(10));
        sensor_axis_sensor_max_set_curr(bse2, 10, K_MSEC(10));
        break;
      
      case INPUT_BTN_DOWN:
        sensor_axis_sensor_min_set_curr(bse1, 10, K_MSEC(10));
        sensor_axis_sensor_min_set_curr(bse2, 10, K_MSEC(10));
        break;
      
      default:
        break;
    }
  }
}

static void blink_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_setting_ctx *ctx = 
      CONTAINER_OF(dwork, struct dashboard_setting_ctx, blink_dwork);

  if(ctx->mode == BRIGHTNESS_SET){
    speed_blink(ctx->blink_state);
    
  }

  if(ctx->mode == APPS_SET) {
    rgb_blink_set(ctx->blink_rgb, LED_STRIP_LEN, ctx->blink_state);
    led_strip_update_rgb(accel_display, ctx->blink_rgb, LED_STRIP_LEN);
  }

  if(ctx->mode == BSE_SET) {
    rgb_blink_set(ctx->blink_rgb, LED_STRIP_LEN, ctx->blink_state);
    led_strip_update_rgb(brake_display, ctx->blink_rgb, LED_STRIP_LEN);
  }

  ctx->blink_state = !ctx->blink_state;
  k_work_reschedule(&ctx->blink_dwork, LED_BLINK_PERIOD);
}


static void modify_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_setting_ctx *ctx =
      CONTAINER_OF(dwork, struct dashboard_setting_ctx, modify_dwork);

  modify_brightness(ctx->states[INCREASING]);

  k_work_reschedule(&ctx->modify_dwork, K_MSEC(100));
}

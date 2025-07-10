// glibc includes
#include <stdbool.h>
#include <stddef.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/input/sensor_axis.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/dt-bindings/input/input-error-codes.h>
#include <zephyr/init.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/msg/msg.h>

// project includes
#include "vcu/ctrl/states.h"

/// @todo APPS auto calibration triggered by micro

/* type ----------------------------------------------------------------------*/
struct cockpit_ctx {
  bool accel_engaged;
  bool brake_engaged;
};

/* static function declaration -----------------------------------------------*/
static void states_update(struct cockpit_ctx* ctx);

static int init();

static void input_cb(struct input_event* evt, void* user_data);

static void raw_cb(const struct device* dev, const struct sensor_value* val,
                   void* user_data);

static void cockpit_publish(const void* data, void* user_data);

/* static variable -----------------------------------------------------------*/
static const struct device* steer = DEVICE_DT_GET(DT_NODELABEL(steer));

static const struct device* accel = DEVICE_DT_GET(DT_NODELABEL(accel));
static const struct device* apps1 =
    DEVICE_DT_GET(DT_NODELABEL(apps1_sensor_axis));
static const struct device* apps2 =
    DEVICE_DT_GET(DT_NODELABEL(apps2_sensor_axis));

static const struct device* brake = DEVICE_DT_GET(DT_NODELABEL(brake));
static const struct device* bse1 =
    DEVICE_DT_GET(DT_NODELABEL(bse1_sensor_axis));
static const struct device* bse2 =
    DEVICE_DT_GET(DT_NODELABEL(bse2_sensor_axis));

static const struct device* accel_pedal_plaus =
    DEVICE_DT_GET(DT_NODELABEL(accel_pedal_plaus));

static struct cockpit_ctx g_ctx = {
    .accel_engaged = false,
    .brake_engaged = false,
};

SYS_INIT(init, APPLICATION, CONFIG_VCU_SENSORS_INIT_PRIORITY);

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

ERR_DEFINE(steer, ERR_CODE_STEER, ERR_SEV_WARN, "Steering encoder error");

ERR_DEFINE(accel, ERR_CODE_ACCEL, ERR_SEV_FATAL, "Accelerator error");
ERR_DEFINE(apps1, ERR_CODE_APPS1, ERR_SEV_INFO, "APPS1 error");
ERR_DEFINE(apps2, ERR_CODE_APPS2, ERR_SEV_INFO, "APPS2 error");

ERR_DEFINE(brake, ERR_CODE_BRAKE, ERR_SEV_FATAL, "Brake error");
ERR_DEFINE(bse1, ERR_CODE_BSE1, ERR_SEV_INFO, "BSE1 error");
ERR_DEFINE(bse2, ERR_CODE_BSE2, ERR_SEV_INFO, "BSE2 error");

ERR_DEFINE(pedal_plaus, ERR_CODE_PEDAL_PLAUS, ERR_SEV_WARN,
           "Pedal plausibility error");

// clang-format off

static AGG_TYPED_DEFINE(cockpit_agg,
    struct msg_cockpit_data, AGG_DATA_INIT(0),
    K_MSEC(10), K_MSEC(8), K_MSEC(3), cockpit_publish, NULL,
    AGG_MEMBER(steer),

    AGG_MEMBER(accel),
    AGG_MEMBER(apps1, AGG_FLAG_OPTIONAL),
    AGG_MEMBER(apps2, AGG_FLAG_OPTIONAL),

    AGG_MEMBER(brake),
    AGG_MEMBER(bse1, AGG_FLAG_OPTIONAL),
    AGG_MEMBER(bse2, AGG_FLAG_OPTIONAL)
);

// clang-format on

/* static function definition ------------------------------------------------*/
static void states_update(struct cockpit_ctx* ctx) {
  if ((states_get() & STATE_RTD_BLINK) && !ctx->accel_engaged &&
      ctx->brake_engaged) {
    states_transition(TRANS_CMD_PEDAL);

  } else if ((states_get() & STATE_RTD_STEADY) &&
             (ctx->accel_engaged || !ctx->brake_engaged)) {
    states_transition(TRANS_CMD_PEDAL_CLEAR);
  }
}

static int init() {
  sensor_axis_sensor_set_raw_cb(apps1, raw_cb, NULL);
  sensor_axis_sensor_set_raw_cb(apps2, raw_cb, NULL);
  sensor_axis_sensor_set_raw_cb(bse1, raw_cb, NULL);
  sensor_axis_sensor_set_raw_cb(bse2, raw_cb, NULL);

  return 0;
}

static void input_cb(struct input_event* evt, void* user_data) {
  struct cockpit_ctx* ctx = user_data;

  if (evt->dev == steer) {
    if (evt->type == INPUT_EV_ABS && evt->code == INPUT_ABS_WHEEL) {
      AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, steer,
                       evt->value);

    } else if (evt->type == INPUT_EV_ERROR) {
      err_report(ERR_CODE_STEER, evt->value);
    }

  } else if (evt->dev == accel) {
    if (evt->type == INPUT_EV_ABS && evt->code == INPUT_ABS_THROTTLE) {
      if (!IS_ENABLED(CONFIG_VCU_SENSORS_PEDAL_PLAUS)) {
        AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, accel,
                         evt->value);
      }

      ctx->accel_engaged = evt->value > 0;

    } else if (evt->type == INPUT_EV_ERROR) {
      err_report(ERR_CODE_ACCEL, evt->value);

      if (evt->value) {
        ctx->accel_engaged = false;
      }
    }

    states_update(ctx);

  } else if (evt->dev == apps1) {
    if (evt->type == INPUT_EV_ERROR) {
      err_report(ERR_CODE_APPS1, evt->value);
    }

  } else if (evt->dev == apps2) {
    if (evt->type == INPUT_EV_ERROR) {
      err_report(ERR_CODE_APPS2, evt->value);
    }

  } else if (evt->dev == brake) {
    if (evt->type == INPUT_EV_ABS && evt->code == INPUT_ABS_BRAKE) {
      AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, brake,
                       evt->value);
      ctx->brake_engaged = evt->value > 0;

    } else if (evt->type == INPUT_EV_ERROR) {
      err_report(ERR_CODE_BRAKE, evt->value);

      if (evt->value) {
        ctx->brake_engaged = false;
      }
    }

    states_update(ctx);

  } else if (evt->dev == bse1) {
    if (evt->type == INPUT_EV_ERROR) {
      err_report(ERR_CODE_BSE1, evt->value);
    }

  } else if (evt->dev == bse2) {
    if (evt->type == INPUT_EV_ERROR) {
      err_report(ERR_CODE_BSE2, evt->value);
    }

  } else if (evt->dev == accel_pedal_plaus) {
    if (evt->type == INPUT_EV_ABS && evt->code == INPUT_ABS_THROTTLE) {
      if (IS_ENABLED(CONFIG_VCU_SENSORS_PEDAL_PLAUS)) {
        AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, accel,
                         evt->value);
      }

    } else if (evt->type == INPUT_EV_ERROR &&
               evt->code == INPUT_ERROR_PEDAL_PLAUS) {
      err_report(ERR_CODE_PEDAL_PLAUS, evt->value);
    }
  }
}

static void raw_cb(const struct device* dev, const struct sensor_value* val,
                   void* user_data) {
  if (dev == apps1) {
    AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, apps1,
                     sensor_value_to_float(val));

  } else if (dev == apps2) {
    AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, apps2,
                     sensor_value_to_float(val));

  } else if (dev == bse1) {
    AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, bse1,
                     sensor_value_to_float(val));

  } else if (dev == bse2) {
    AGG_TYPED_UPDATE(&cockpit_agg, struct msg_cockpit_data, bse2,
                     sensor_value_to_float(val));
  }
}

static void cockpit_publish(const void* data, void* user_data) {
  (void)user_data;

  struct msg_cockpit_data* msg = (struct msg_cockpit_data*)data;
  msg_header_init(&msg->header);

  zbus_chan_pub(&msg_cockpit_data_chan, msg, K_MSEC(5));
}

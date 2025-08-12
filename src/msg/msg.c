#include "vcu/msg/msg.h"

// glibc includes
#include <stddef.h>
#include <string.h>
#include <time.h>

// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/clock.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/logging.h>
#include <nturt/msg/msg.h>
#include <nturt/sys/fs.h>

// project includes
#include "vcu/ctrl/states.h"

// sizeof includes the null terminating character, which can be used to
// represent the size of '/'.
BUILD_ASSERT(sizeof(CONFIG_VCU_MSG_LOGGING_DIR) +
                     sizeof("1970_01_01_00_00_00") <
                 FS_MAX_PATH_LEN,
             "Path too long");

LOG_MODULE_REGISTER(vcu_msg);

/* static function declaration -----------------------------------------------*/
static void states_cb(enum states_state state, bool is_entry, void *user_data);

/* static variable -----------------------------------------------------------*/
const struct zbus_channel *logged_chans[] = {
    &msg_sensor_cockpit_chan, &msg_sensor_wheel_chan, &msg_sensor_pow_chan,
    &msg_ctrl_torque_chan,    &msg_ctrl_word_chan,    &msg_states_chan,
};

MSG_CHAN_DEFINE(MSG_VCU_LIST);

STATES_CALLBACK_DEFINE(STATE_RUNNING, states_cb, NULL);

/* static function definition ------------------------------------------------*/
static void states_cb(enum states_state state, bool is_entry, void *user_data) {
  (void)state;
  (void)user_data;

  if (is_entry) {
    char path[FS_MAX_PATH_LEN];
    char *p = stpcpy(path, CONFIG_VCU_MSG_LOGGING_DIR);
    *p = '/';
    p++;

    struct timespec ts;
    sys_clock_gettime(SYS_CLOCK_REALTIME, &ts);
    p += strftime(p, sizeof(path) - (p - path), "%Y_%m_%d_%H_%M_%S",
                  gmtime(&ts.tv_sec));
    *p = '/';
    p++;

    ARRAY_FOR_EACH_PTR(logged_chans, chan) {
      __ASSERT(p - path + strlen(zbus_chan_name(*chan)) + strlen(".csv") <
                   FS_MAX_PATH_LEN,
               "Path too long");

      sprintf(p, "%s.csv", zbus_chan_name(*chan));
      msg_chan_logging_start(*chan, path);
    }

  } else {
    ARRAY_FOR_EACH_PTR(logged_chans, chan) { msg_chan_logging_stop(*chan); }
  }
}

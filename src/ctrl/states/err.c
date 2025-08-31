// zephyr includes
#include <zephyr/sys/util.h>

// nturt includes
#include <nturt/err/err.h>

// project includes
#include "vcu/ctrl/states.h"

/* macro ---------------------------------------------------------------------*/
#ifdef CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_FATAL
#define FILTERED_ERRORS ERR_SEV_FATAL
#elif defined(CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_ERROR)
#define FILTERED_ERRORS ERR_SEV_FATAL, ERR_SEV_ERROR
#elif defined(CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_WARNING)
#define FILTERED_ERRORS ERR_SEV_FATAL, ERR_SEV_ERROR, ERR_SEV_WARNING
#endif

#define ON_SEVERITY (FOR_EACH(IDENTITY, (|), FILTERED_ERRORS))

/* static function declaration -----------------------------------------------*/
static void err_cb(uint32_t errcode, bool set, void* user_data);

/* static variable -----------------------------------------------------------*/
ERR_CALLBACK_DEFINE(err_cb, NULL, ERR_FILTER_SEV(FILTERED_ERRORS));

/* static function definition ------------------------------------------------*/
static void err_cb(uint32_t errcode, bool set, void* user_data) {
  (void)errcode;
  (void)set;
  (void)user_data;

  int max_severity = 0;

  struct err* err;
  ERR_FOREACH_SET(err) {
    max_severity = MAX(max_severity, err->flags & ON_SEVERITY);
  }

  if (max_severity == ERR_SEV_FATAL) {
    if (states_valid_transition(TRANS_CMD_FATAL_ERROR)) {
      states_transition(TRANS_CMD_FATAL_ERROR);
    }

  } else if (max_severity != 0) {
    if (states_valid_transition(TRANS_CMD_ERROR)) {
      states_transition(TRANS_CMD_ERROR);
    } else if (states_valid_transition(TRANS_CMD_ERROR_RUNNING)) {
      states_transition(TRANS_CMD_ERROR_RUNNING);
    }

  } else {
    if (states_valid_transition(TRANS_CMD_ERROR_CLEARED)) {
      states_transition(TRANS_CMD_ERROR_CLEARED);
    } else if (states_valid_transition(TRANS_CMD_ERROR_CLEARED_RUNNING)) {
      states_transition(TRANS_CMD_ERROR_CLEARED_RUNNING);
    }
  }
}

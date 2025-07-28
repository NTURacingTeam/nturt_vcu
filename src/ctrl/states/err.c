// nturt includes
#include <nturt/err/err.h>

// project includes
#include "vcu/ctrl/states.h"

#ifndef CONFIG_VCU_STATES_TRANS_TO_ERROR_DISABLED

/* macro ---------------------------------------------------------------------*/
#ifdef CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_FATAL
#define ON_SEVERITY (ERR_SEV_FATAL)
#elif defined(CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_WARNING)
#define ON_SEVERITY (ERR_SEV_WARNING)
#endif

#define MONITORED_ERROR                                             \
  ERR_CODE_ACCEL, ERR_CODE_BRAKE, ERR_CODE_INV_FL, ERR_CODE_INV_FR, \
      ERR_CODE_INV_RL, ERR_CODE_INV_RR

/* static function declaration -----------------------------------------------*/
static void err_handler(uint32_t errcode, bool set, void* user_data);

/* static variable -----------------------------------------------------------*/
static const uint32_t codes[] = {MONITORED_ERROR};

ERR_CALLBACK_DEFINE(err_handler, NULL, ERR_FILTER_CODE(MONITORED_ERROR));

/* static function definition ------------------------------------------------*/
static void err_handler(uint32_t errcode, bool set, void* user_data) {
  (void)errcode;
  (void)set;
  (void)user_data;

  for (int i = 0; i < ARRAY_SIZE(codes); i++) {
    if (err_is_set(codes[i])) {
      if (states_get() & STATE_ERR_FREE) {
        states_transition(TRANS_CMD_ERR);
      }

      return;
    }
  }

  if (states_get() & STATE_ERR) {
    states_transition(TRANS_CMD_ERR_CLEAR);
  }
}

#endif  // CONFIG_VCU_STATES_TRANS_TO_ERROR_DISABLED

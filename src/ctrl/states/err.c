// nturt includes
#include <nturt/err/err.h>

// project includes
#include "vcu/ctrl/states.h"

/* macro ---------------------------------------------------------------------*/
#ifdef CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_FATAL
#define ON_SEVERITY (ERR_SEV_FATAL)
#elif defined(CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_WARNING)
#define ON_SEVERITY (ERR_SEV_WARNING)
#endif

/* static function declaration -----------------------------------------------*/
static void err_handler(uint32_t errcode, bool set, void* user_data);

/* static variable -----------------------------------------------------------*/
ERR_CALLBACK_DEFINE(err_handler, NULL, ERR_FILTER_SEV(ON_SEVERITY));

/* static function definition ------------------------------------------------*/
static void err_handler(uint32_t errcode, bool set, void* user_data) {
  (void)errcode;
  (void)set;
  (void)user_data;

  struct err* err;
  ERR_FOREACH_SET(err) {
    if (err->flags & ON_SEVERITY) {
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

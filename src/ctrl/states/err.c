// nturt includes
#include <nturt/err.h>

// project includes
#include "vcu/ctrl/states.h"

/* macro ---------------------------------------------------------------------*/
#define TRIG_SEV (ERR_SEV_FATAL)

/* static function declaration -----------------------------------------------*/
void states_err_handler(uint32_t errcode, bool set, void* user_data);

/* static variable -----------------------------------------------------------*/
ERR_CALLBACK_DEFINE(states_err_handler, NULL, ERR_FILTER_SEV(TRIG_SEV));

/* static function definition ------------------------------------------------*/
void states_err_handler(uint32_t errcode, bool set, void* user_data) {
  (void)errcode;
  (void)set;
  (void)user_data;

  struct err* err;
  ERR_FOREACH_SET(err) {
    if (err->flags & ERR_FLAG_SET) {
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

/**
 * @file
 * @brief Control system.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-02-24
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_CTRL_H_
#define VCU_CTRL_H_

// glibc includes
#include <stdint.h>

// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

/**
 * @defgroup ctrl Control
 * @brief Control system.
 *
 * @{
 */

/* macro ---------------------------------------------------------------------*/
#define TORQ_DEFAULT 50

/**
 * @brief Specify aa control parameter. Used in @ref CTRL_PARAM_DECLARE,
 * @ref CTRL_PARAM_DEFINE and @ref CTRL_PARAM_EXTERN.
 *
 * @param[in] name Name of the parameter.
 * @param[in] type Type of the parameter.
 * @param[in] default Default value of the parameter.
 */
#define CTRL_PARAM(name, type, default) (name, type, default)

#define _CTRL_PARAM_NAME(param) GET_ARG_N(1, __DEBRACKET param)
#define _CTRL_PARAM_TYPE(param) GET_ARG_N(2, __DEBRACKET param)
#define _CTRL_PARAM_DEFAULT(param) GET_ARG_N(3, __DEBRACKET param)

#define _CTRL_PARAM_SET(name) CONCAT(ctrl_param_, name, _set)
#define _CTRL_PARAM_GET(name) CONCAT(ctrl_param_, name, _get)

#define _CTRL_PARAM_DECLARE(param)                                            \
  void _CTRL_PARAM_SET(_CTRL_PARAM_NAME(param))(_CTRL_PARAM_TYPE(param) val); \
  _CTRL_PARAM_TYPE(param) _CTRL_PARAM_GET(_CTRL_PARAM_NAME(param))()

/**
 * @brief Declare control parameters in setter and getter functions.
 *
 * @param[in] ... Control parameters to declare, must be specified by
 * @ref CTRL_PARAM.
 */
#define CTRL_PARAM_DECLARE(...) FOR_EACH(_CTRL_PARAM_DECLARE, (;), __VA_ARGS__)

#define _CTRL_PARAM_EXTERN(param) \
  extern _CTRL_PARAM_TYPE(param) _CTRL_PARAM_NAME(param)

/**
 * @brief Declare control parameters as extern variables.
 *
 * @param[in] ... Control parameters to declare, must be specified by
 * @ref CTRL_PARAM.
 */
#define CTRL_PARAM_EXTERN(...) FOR_EACH(_CTRL_PARAM_EXTERN, (;), __VA_ARGS__)

#define _CTRL_PARAM_DEFINE(param)                                              \
  _CTRL_PARAM_TYPE(param)                                                      \
  _CTRL_PARAM_NAME(param) = _CTRL_PARAM_DEFAULT(param);                        \
                                                                               \
  void _CTRL_PARAM_SET(_CTRL_PARAM_NAME(param))(_CTRL_PARAM_TYPE(param) val) { \
    k_mutex_lock(&g_ctx.lock, K_FOREVER);                                      \
                                                                               \
    _CTRL_PARAM_NAME(param) = val;                                             \
                                                                               \
    k_mutex_unlock(&g_ctx.lock);                                               \
  }                                                                            \
                                                                               \
  _CTRL_PARAM_TYPE(param) _CTRL_PARAM_GET(_CTRL_PARAM_NAME(param))() {         \
    return _CTRL_PARAM_NAME(param);                                            \
  }

/**
 * @brief Define control parameters and their getter/setter functions.
 *
 * @param[in] ... Control parameters to define, must be specified by
 * @ref CTRL_PARAM.
 */
#define CTRL_PARAM_DEFINE(list) FOR_EACH(_CTRL_PARAM_DEFINE, (), list)

/// @brief List of control parameters.
#define CTRL_PARAM_LIST                           \
  CTRL_PARAM(torq_fl, uint8_t, TORQ_DEFAULT),     \
      CTRL_PARAM(torq_fr, uint8_t, TORQ_DEFAULT), \
      CTRL_PARAM(torq_rl, uint8_t, TORQ_DEFAULT), \
      CTRL_PARAM(torq_rr, uint8_t, TORQ_DEFAULT)

/* function declaration ------------------------------------------------------*/
CTRL_PARAM_DECLARE(CTRL_PARAM_LIST);

/**
 * @brief Save current control parameter settings.
 *
 * @return 0 on success, negative error code on failure.
 */
int ctrl_settings_save();

/**
 * @} // ctrl
 */

#endif  // VCU_CTRL_H_

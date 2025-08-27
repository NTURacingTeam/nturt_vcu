/**
 * @file
 * @brief Control system parameters.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-08-24
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_CTRL_PARAMS_H
#define VCU_CTRL_PARAMS_H

// glibc includes
#include <stdint.h>

// zephyr includes
#include <zephyr/sys/util.h>

/**
 * @addtogroup ctrl_param Control parameters.
 * @brief Control system parameters.
 *
 * @ingroup ctrl
 * @{
 */

/* macro ---------------------------------------------------------------------*/
// constants
#define PARAM_MOTOR_DIR_L -1.0
#define PARAM_MOTOR_DIR_R 1.0
#define PARAM_MOTOR_RATED_TORQUE 20.0
#define PARAM_MOTOR_REDUCTION_RATIO 13.1

// defaults
#define PARAM_TORQ_LIMIT 20.0
#define PARAM_TORQ_SLEW 4.0

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
 * @brief Declare control parameters in getter (`ctrl_param_<name>_get`) and
 * setter (`ctrl_param_<name>_set`) functions.
 *
 * @param[in] ... Control parameters to declare, must be specified by
 * @ref CTRL_PARAM.
 */
#define CTRL_PARAM_DECLARE(...) FOR_EACH(_CTRL_PARAM_DECLARE, (;), __VA_ARGS__)

#define _CTRL_PARAM_EXTERN(param) \
  volatile extern _CTRL_PARAM_TYPE(param) _CTRL_PARAM_NAME(param)

/**
 * @brief Declare control parameters as extern variables.
 *
 * @param[in] ... Control parameters to declare, must be specified by
 * @ref CTRL_PARAM.
 */
#define CTRL_PARAM_EXTERN(...) FOR_EACH(_CTRL_PARAM_EXTERN, (;), __VA_ARGS__)

/// @brief List of control parameters.
#define CTRL_PARAM_LIST                                                    \
  CTRL_PARAM(torq_limit_fl, double, PARAM_TORQ_LIMIT),                     \
      CTRL_PARAM(torq_limit_fr, double, PARAM_TORQ_LIMIT),                 \
      CTRL_PARAM(torq_limit_rl, double, PARAM_TORQ_LIMIT),                 \
      CTRL_PARAM(torq_limit_rr, double, PARAM_TORQ_LIMIT),                 \
      CTRL_PARAM(torq_slew, double, PARAM_TORQ_SLEW),                      \
      CTRL_PARAM(torq_derate_begin, double, 3000.0),                       \
      CTRL_PARAM(torq_derate_end, double, 5000.0),                         \
      CTRL_PARAM(fb_ratio, double, 0.5), CTRL_PARAM(tv_gain, double, 2.0), \
      CTRL_PARAM(target_sr, double, 0.1)

/* function declaration ------------------------------------------------------*/
CTRL_PARAM_DECLARE(CTRL_PARAM_LIST);

/**
 * @} // ctrl_param
 */

#endif  // VCU_CTRL_PARAMS_H

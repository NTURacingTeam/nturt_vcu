#ifndef VCU_ERR_H_
#define VCU_ERR_H_

/// @brief Define the error code list.
#define ERR_CODE_LIST                                                          \
  ERR_CODE_LISTIFY(                                                            \
      ERR_CODE(NODE_FB, ERR_SEV_FATAL), ERR_CODE(NODE_RB, ERR_SEV_FATAL),      \
      ERR_CODE(NODE_RPI, ERR_SEV_FATAL), ERR_CODE(NODE_ACC, ERR_SEV_FATAL),    \
      ERR_CODE(NODE_INV_FL, ERR_SEV_FATAL),                                    \
      ERR_CODE(NODE_INV_FR, ERR_SEV_FATAL),                                    \
      ERR_CODE(NODE_INV_RL, ERR_SEV_FATAL),                                    \
      ERR_CODE(NODE_INV_RR, ERR_SEV_FATAL), ERR_CODE(CAN, ERR_SEV_FATAL),      \
      ERR_CODE(STEER, ERR_SEV_FATAL), ERR_CODE(APPS1, ERR_SEV_FATAL),          \
      ERR_CODE(APPS2, ERR_SEV_FATAL), ERR_CODE(APPS_PLAUS, ERR_SEV_FATAL),     \
      ERR_CODE(BSE_F, ERR_SEV_FATAL), ERR_CODE(BSE_R, ERR_SEV_FATAL),          \
      ERR_CODE(PEDAL_PLAUS, ERR_SEV_WARN),                                     \
      ERR_CODE(WHEEL_SPEED_L, ERR_SEV_FATAL),                                  \
      ERR_CODE(WHEEL_SPEED_R, ERR_SEV_FATAL),                                  \
      ERR_CODE(SUSP_DIVE, ERR_SEV_WARN), ERR_CODE(SUSP_ROLL, ERR_SEV_WARN),    \
      ERR_CODE(STAT_ACC, ERR_SEV_FATAL), ERR_CODE(STAT_INV_FL, ERR_SEV_FATAL), \
      ERR_CODE(STAT_INV_FR, ERR_SEV_FATAL),                                    \
      ERR_CODE(STAT_INV_RL, ERR_SEV_FATAL),                                    \
      ERR_CODE(STAT_INV_RR, ERR_SEV_FATAL))

#endif  // VCU_ERR_H_

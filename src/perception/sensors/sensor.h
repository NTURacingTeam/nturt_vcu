// zephyr includes
#include <zephyr/kernel.h>

/* macro ---------------------------------------------------------------------*/
#define SENSOR_POW_PERIOD K_MSEC(100)

/* exported variable ---------------------------------------------------------*/
extern struct k_work_q *sensor_work_q;

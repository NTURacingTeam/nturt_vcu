// zephyr includes
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

/* static function declaration -----------------------------------------------*/
static int init();

/* static variable -----------------------------------------------------------*/
SYS_INIT(init, APPLICATION, UTIL_DEC(CONFIG_VCU_SENSORS_INIT_PRIORITY));

static K_THREAD_STACK_DEFINE(sensor_work_q_stack, 1024);

/* exported variable ---------------------------------------------------------*/
struct k_work_q *sensor_work_q = &(struct k_work_q){0};

/* static function definition ------------------------------------------------*/
static int init() {
  struct k_work_queue_config config = {
      .name = "sensor_work_queue",
  };

  k_work_queue_init(sensor_work_q);
  k_work_queue_start(sensor_work_q, sensor_work_q_stack,
                     K_THREAD_STACK_SIZEOF(sensor_work_q_stack), 5, &config);
  return 0;
}

// zephyr includes
#include <zephyr/kernel.h>

/* static function declaration -----------------------------------------------*/
static void thread(void *arg1, void *arg2, void *arg3);

// K_THREAD_DEFINE(ctrl_thread, 1024, thread, NULL, NULL, NULL, 0, 0, 0);

/* static function definition ------------------------------------------------*/
static void thread(void *arg1, void *arg2, void *arg3) {
  (void)arg1;
  (void)arg2;
  (void)arg3;
}

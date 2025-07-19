// glibc includes
#include <stdbool.h>
#include <stdio.h>

// zephyr includes
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

// nturt includes
#include <nturt/canbus/canopen.h>
#include <nturt/telemetry.h>

// project includes
#include "vcu/telemetry.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main() {
  while (true) {
    k_sleep(K_MSEC(1000));
  }

  return 0;
}

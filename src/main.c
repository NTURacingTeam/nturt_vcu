// glibc include
#include <stdbool.h>

// zephyr include
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static const struct device *speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));
static const struct device *battery_display =
    DEVICE_DT_GET(DT_NODELABEL(battery_display));

static const struct device *accel_display =
    DEVICE_DT_GET(DT_NODELABEL(accel_display));
static const struct device *brake_display =
    DEVICE_DT_GET(DT_NODELABEL(brake_display));

char *num_char(int i) {
  static char buf[20];
  if (i < 10) {
    snprintf(buf, sizeof(buf), ".%d", i);
  } else {
    snprintf(buf, sizeof(buf), "%2d.", i);
  }

  return buf;
}

void rgb_set_level(struct led_rgb *rgb, int level) {
  for (int i = 0; i < level; i++) {
    rgb[i].r = 1;
  }

  for (int i = level; i < 20; i++) {
    rgb[i].r = 0;
  }
}

int main() {
  int ret;
  int i = 0;
  struct led_rgb rgb[20];

  while (true) {
    i = (i + 1) % 100;

    auxdisplay_brightness_set(speed_display, i);

    char *num_str = num_char(i);
    ret = auxdisplay_write(speed_display, num_str, strlen(num_str));
    if (ret < 0) {
      LOG_ERR("Failed to write to speed_display: %s", strerror(-ret));
    }

    num_str = num_char(100 - i);
    ret = auxdisplay_write(battery_display, num_str, strlen(num_str));
    if (ret < 0) {
      LOG_ERR("Failed to write to speed_display: %s", strerror(-ret));
    }

    rgb_set_level(rgb, i % 20);
    ret = led_strip_update_rgb(accel_display, rgb, 20);
    if (ret < 0) {
      LOG_ERR("Failed to update led strip: %s", strerror(-ret));
    }

    rgb_set_level(rgb, 20 - i % 20);
    ret = led_strip_update_rgb(brake_display, rgb, 20);
    if (ret < 0) {
      LOG_ERR("Failed to update led strip: %s", strerror(-ret));
    }
    k_sleep(K_MSEC(100));
  }

  return 0;
}

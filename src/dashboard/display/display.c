// zephyr includes
#include <zephyr/init.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>

// lvgl includes
#include <lvgl.h>

LV_IMAGE_DECLARE(img_logo);

/* static function declarartion ----------------------------------------------*/
int init();

/* static variable -----------------------------------------------------------*/
static const struct device* display =
    DEVICE_DT_GET(DT_NODELABEL(display));

SYS_INIT(init, APPLICATION, 99);

int init() {
  lv_obj_t* logo = lv_image_create(lv_screen_active());

  lv_image_set_src(logo, &img_logo);
  lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);

	lv_timer_handler();
	display_blanking_off(display);

  return 0;
}

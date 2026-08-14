// lv_port_touch.h
#ifndef LV_PORT_TOUCH_H
#define LV_PORT_TOUCH_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

void lv_port_touch_init(void);
void lv_port_touch_read(lv_indev_t *indev, lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif

#endif // LV_PORT_TOUCH_H

#include <Arduino.h>
#include <lvgl.h>

#include "Arduino_GFX_Library.h"
#include "Arduino_DriveBus_Library.h"

#include "pin_config.h"


#define WIDTH 240
#define HEIGHT 280


Arduino_DataBus *bus =
new Arduino_ESP32SPI(
LCD_DC,
LCD_CS,
LCD_SCK,
LCD_MOSI
);


Arduino_GFX *gfx =
new Arduino_ST7789(
bus,
LCD_RST,
0,
true,
WIDTH,
HEIGHT
);



static lv_disp_draw_buf_t draw_buf;

static lv_color_t buf[
WIDTH * HEIGHT / 10
];



void flush(
lv_disp_drv_t *drv,
const lv_area_t *area,
lv_color_t *color
){

uint32_t w =
area->x2-area->x1+1;

uint32_t h =
area->y2-area->y1+1;


gfx->draw16bitRGBBitmap(
area->x1,
area->y1,
(uint16_t*)color,
w,
h
);


lv_disp_flush_ready(drv);

}



void setup()
{

Serial.begin(115200);


gfx->begin();


pinMode(
LCD_BL,
OUTPUT
);

digitalWrite(
LCD_BL,
HIGH
);



lv_init();



lv_disp_draw_buf_init(
&draw_buf,
buf,
NULL,
WIDTH*HEIGHT/10
);



static lv_disp_drv_t disp;

lv_disp_drv_init(&disp);


disp.hor_res = WIDTH;
disp.ver_res = HEIGHT;

disp.flush_cb = flush;

disp.draw_buf=&draw_buf;


lv_disp_drv_register(&disp);



lv_obj_t *label =
lv_label_create(
lv_scr_act()
);


lv_label_set_text(
label,
"BarakatTime\nLVGL"
);


lv_obj_center(label);


}



void loop()
{

lv_timer_handler();

delay(5);

}

#include <Arduino.h>

#include <lvgl.h>

#include "Arduino_GFX_Library.h"

#include "lv_conf.h"
#include "pin_config.h"



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
    LCD_WIDTH,
    LCD_HEIGHT,
    0,
    20,
    0,
    0
);



static lv_disp_draw_buf_t draw_buf;

static lv_color_t buf1[LCD_WIDTH * 40];



void my_disp_flush(
    lv_disp_drv_t *disp,
    const lv_area_t *area,
    lv_color_t *color_p
)
{

    uint32_t w =
    area->x2 - area->x1 + 1;


    uint32_t h =
    area->y2 - area->y1 + 1;


    gfx->draw16bitRGBBitmap(
        area->x1,
        area->y1,
        (uint16_t *)&color_p->full,
        w,
        h
    );


    lv_disp_flush_ready(disp);

}



void setup()
{

    Serial.begin(115200);


    pinMode(
        LCD_BL,
        OUTPUT
    );

    digitalWrite(
        LCD_BL,
        HIGH
    );


    gfx->begin();


    gfx->fillScreen(
        BLACK
    );



    lv_init();



    lv_disp_draw_buf_init(
        &draw_buf,
        buf1,
        NULL,
        LCD_WIDTH*40
    );



    static lv_disp_drv_t disp_drv;


    lv_disp_drv_init(
        &disp_drv
    );


    disp_drv.hor_res = LCD_WIDTH;

    disp_drv.ver_res = LCD_HEIGHT;

    disp_drv.flush_cb = my_disp_flush;

    disp_drv.draw_buf = &draw_buf;


    lv_disp_drv_register(
        &disp_drv
    );



    lv_obj_t *label =
    lv_label_create(
        lv_scr_act()
    );


    lv_label_set_text(
        label,
        "Waveshare\nLVGL 8.4"
    );


    lv_obj_set_style_text_color(
        label,
        lv_color_hex(0xFFD700),
        0
    );


    lv_obj_align(
        label,
        LV_ALIGN_CENTER,
        0,
        0
    );

}



void loop()
{

    lv_timer_handler();

    delay(5);

}

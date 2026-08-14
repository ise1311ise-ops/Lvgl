#include <Arduino.h>
#include "Arduino_GFX_Library.h"
#include <lvgl.h>


#define LCD_WIDTH   240
#define LCD_HEIGHT  280

#define LCD_DC      4
#define LCD_CS      5
#define LCD_SCK     6
#define LCD_MOSI    7
#define LCD_RST     8
#define LCD_BL      15



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

static lv_color_t buffer[240 * 40];



void lv_flush(
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


    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH);



    if(!gfx->begin())
    {
        Serial.println("GFX ERROR");
    }


    gfx->fillScreen(
        BLACK
    );



    lv_init();



    lv_disp_draw_buf_init(
        &draw_buf,
        buffer,
        NULL,
        240*40
    );



    static lv_disp_drv_t disp_drv;


    lv_disp_drv_init(
        &disp_drv
    );


    disp_drv.hor_res = 240;
    disp_drv.ver_res = 280;

    disp_drv.flush_cb = lv_flush;

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
        "LVGL 8.4\nWaveshare ESP32-S3"
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

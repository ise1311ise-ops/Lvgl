#include <Arduino.h>

#include <lvgl.h>

#include "Arduino_GFX_Library.h"
#include "Arduino_DriveBus_Library.h"

#include "pin_config.h"


#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 280


Arduino_DataBus *bus = new Arduino_ESP32SPI(
    LCD_DC,
    LCD_CS,
    LCD_SCK,
    LCD_MOSI
);


Arduino_GFX *gfx = new Arduino_ST7789(
    bus,
    LCD_RST,
    0,
    true,
    SCREEN_WIDTH,
    SCREEN_HEIGHT
);


static lv_disp_draw_buf_t draw_buf;

static lv_color_t buf1[SCREEN_WIDTH * SCREEN_HEIGHT / 10];


void my_disp_flush(
    lv_disp_drv_t *disp,
    const lv_area_t *area,
    lv_color_t *color_p
)
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;


    gfx->draw16bitRGBBitmap(
        area->x1,
        area->y1,
        (uint16_t *)color_p,
        w,
        h
    );


    lv_disp_flush_ready(disp);
}



void create_ui()
{

    lv_obj_t *label = lv_label_create(
        lv_scr_act()
    );


    lv_label_set_text(
        label,
        "BarakatTime\nLVGL TEST"
    );


    lv_obj_align(
        label,
        LV_ALIGN_CENTER,
        0,
        0
    );


    lv_obj_set_style_text_font(
        label,
        &lv_font_montserrat_28,
        0
    );

}



void setup()
{

    Serial.begin(115200);


    gfx->begin();

    gfx->fillScreen(
        BLACK
    );


    lv_init();


    lv_disp_draw_buf_init(
        &draw_buf,
        buf1,
        NULL,
        SCREEN_WIDTH * SCREEN_HEIGHT / 10
    );


    static lv_disp_drv_t disp_drv;

    lv_disp_drv_init(
        &disp_drv
    );


    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;

    disp_drv.flush_cb =
        my_disp_flush;

    disp_drv.draw_buf =
        &draw_buf;


    lv_disp_drv_register(
        &disp_drv
    );


    create_ui();


}



void loop()
{

    lv_timer_handler();

    delay(5);

}

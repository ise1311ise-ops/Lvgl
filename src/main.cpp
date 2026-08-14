#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>


TFT_eSPI tft = TFT_eSPI();


static lv_disp_draw_buf_t draw_buf;

static lv_color_t buf[240 * 40];


void flush_display(
    lv_disp_drv_t *disp,
    const lv_area_t *area,
    lv_color_t *color_p
)
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;


    tft.startWrite();

    tft.setAddrWindow(
        area->x1,
        area->y1,
        w,
        h
    );


    tft.pushColors(
        (uint16_t *)&color_p->full,
        w*h,
        true
    );


    tft.endWrite();


    lv_disp_flush_ready(disp);
}



void setup()
{

    Serial.begin(115200);


    tft.begin();

    tft.setRotation(0);

    tft.fillScreen(TFT_BLACK);



    lv_init();


    lv_disp_draw_buf_init(
        &draw_buf,
        buf,
        NULL,
        240*40
    );


    static lv_disp_drv_t disp_drv;


    lv_disp_drv_init(
        &disp_drv
    );


    disp_drv.hor_res = 240;
    disp_drv.ver_res = 280;

    disp_drv.flush_cb = flush_display;

    disp_drv.draw_buf = &draw_buf;


    lv_disp_drv_register(
        &disp_drv
    );



    lv_obj_t *title =
        lv_label_create(
            lv_scr_act()
        );


    lv_label_set_text(
        title,
        "LVGL 8.4\nESP32-S3"
    );


    lv_obj_set_style_text_color(
        title,
        lv_color_hex(0xFFD700),
        0
    );


    lv_obj_align(
        title,
        LV_ALIGN_CENTER,
        0,
        -30
    );



    lv_obj_t *box =
        lv_btn_create(
            lv_scr_act()
        );


    lv_obj_set_size(
        box,
        150,
        60
    );


    lv_obj_align(
        box,
        LV_ALIGN_CENTER,
        0,
        50
    );



    lv_obj_t *txt =
        lv_label_create(box);


    lv_label_set_text(
        txt,
        "TEST"
    );


    lv_obj_center(txt);

}



void loop()
{
    lv_timer_handler();

    delay(5);
}

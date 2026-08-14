#include <Arduino.h>
#include <lvgl.h>
#include "lv_port_disp.h"
#include "lv_port_touch.h"
#include "pin_config.h"
#include <WiFi.h>
#include <Wire.h>
#include "SensorPCF85063.hpp"

// LVGL объекты
static lv_obj_t *screen_main;
static lv_obj_t *label_counter;
static lv_obj_t *arc_progress;
static lv_obj_t *label_zikr_name;

// Состояние
static uint32_t tasbeeh_count = 0;
static const char* zikr_names[] = {"SubhanAllah", "Alhamdulillah", "AllahuAkbar", "LaIlahaIllaAllah"};
static uint8_t current_zikr = 0;

// Цветовая палитра
#define COLOR_BG        lv_color_hex(0x0120)
#define COLOR_GOLD      lv_color_hex(0xFD20)
#define COLOR_CARD_BG   lv_color_hex(0x1A42)
#define COLOR_TEXT_DIM  lv_color_hex(0x7BEF)

// Создание стилей
static lv_style_t style_bg;
static lv_style_t style_card;
static lv_style_t style_gold_text;
static lv_style_t style_dim_text;

void setup_styles()
{
    // Стиль фона
    lv_style_init(&style_bg);
    lv_style_set_bg_color(&style_bg, COLOR_BG);
    lv_style_set_bg_opa(&style_bg, LV_OPA_COVER);
    
    // Стиль карточки
    lv_style_init(&style_card);
    lv_style_set_bg_color(&style_card, COLOR_CARD_BG);
    lv_style_set_bg_opa(&style_card, LV_OPA_COVER);
    lv_style_set_radius(&style_card, 14);
    lv_style_set_border_color(&style_card, lv_color_hex(0x3AA6));
    lv_style_set_border_width(&style_card, 1);
    lv_style_set_border_opa(&style_card, LV_OPA_COVER);
    
    // Стиль золотого текста
    lv_style_init(&style_gold_text);
    lv_style_set_text_color(&style_gold_text, COLOR_GOLD);
    lv_style_set_text_font(&style_gold_text, &lv_font_montserrat_28);
    
    // Стиль приглушенного текста
    lv_style_init(&style_dim_text);
    lv_style_set_text_color(&style_dim_text, COLOR_TEXT_DIM);
    lv_style_set_text_font(&style_dim_text, &lv_font_montserrat_14);
}

void create_tasbeeh_screen()
{
    screen_main = lv_obj_create(NULL);
    lv_obj_add_style(screen_main, &style_bg, 0);
    
    // Заголовок
    lv_obj_t *label_title = lv_label_create(screen_main);
    lv_label_set_text(label_title, "TASBEEH");
    lv_obj_add_style(label_title, &style_dim_text, 0);
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 20);
    
    // Дуга прогресса
    arc_progress = lv_arc_create(screen_main);
    lv_obj_set_size(arc_progress, 200, 200);
    lv_obj_center(arc_progress);
    lv_arc_set_range(arc_progress, 0, 33);
    lv_arc_set_value(arc_progress, 0);
    lv_arc_set_rotation(arc_progress, 270);
    lv_arc_set_bg_angles(arc_progress, 0, 360);
    
    // Цвета дуги
    lv_obj_set_style_arc_color(arc_progress, COLOR_GOLD, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc_progress, 10, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc_progress, lv_color_hex(0x9440), LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc_progress, 10, LV_PART_MAIN);
    lv_obj_set_style_arc_opa(arc_progress, LV_OPA_TRANSP, LV_PART_KNOB);
    
    // Счетчик
    label_counter = lv_label_create(screen_main);
    lv_label_set_text(label_counter, "0");
    lv_obj_add_style(label_counter, &style_gold_text, 0);
    lv_obj_align(label_counter, LV_ALIGN_CENTER, 0, -20);
    
    // Название зикра
    label_zikr_name = lv_label_create(screen_main);
    lv_label_set_text(label_zikr_name, zikr_names[current_zikr]);
    lv_obj_add_style(label_zikr_name, &style_dim_text, 0);
    lv_obj_align(label_zikr_name, LV_ALIGN_CENTER, 0, 30);
    
    // Обработчик нажатий
    lv_obj_add_event_cb(screen_main, [](lv_event_t *e) {
        tasbeeh_count++;
        char buf[16];
        snprintf(buf, sizeof(buf), "%lu", (unsigned long)tasbeeh_count);
        lv_label_set_text(label_counter, buf);
        lv_arc_set_value(arc_progress, tasbeeh_count % 33);
    }, LV_EVENT_CLICKED, NULL);
}

void setup()
{
    Serial.begin(115200);
    delay(200);
    Serial.println("BarakatTime with LVGL");
    
    // Инициализация LVGL
    lv_port_disp_init();
    lv_port_touch_init();
    
    // Создание стилей и экрана
    setup_styles();
    create_tasbeeh_screen();
    lv_screen_load(screen_main);
    
    // Настройка таймера LVGL
    // Используем millis() для tick
}

void loop()
{
    lv_timer_handler();
    delay(5);
}

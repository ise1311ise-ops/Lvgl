// lv_port_disp.cpp
#include "lv_port_disp.h"
#include <Arduino_GFX_Library.h>

// Экран
Arduino_DataBus *bus = new Arduino_ESP32SPI(LCD_DC, LCD_CS, LCD_SCK, LCD_MOSI);
Arduino_GFX *gfx = new Arduino_ST7789(bus, LCD_RST, 0, true, LCD_WIDTH, LCD_HEIGHT, 0, 20, 0, 0);

static lv_display_t *display;
static uint8_t *draw_buf_1;
static uint8_t *draw_buf_2;

void lv_port_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)px_map, w, h);
    
    lv_display_flush_ready(disp);
}

void lv_port_disp_init(void)
{
    // Инициализация дисплея
    if (!gfx->begin()) {
        Serial.println("gfx->begin() failed!");
    }
    
    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH);
    
    // Выделение буферов для LVGL
    uint32_t buf_size = LCD_WIDTH * 40; // 40 строк буфера
    
    draw_buf_1 = (uint8_t*)heap_caps_malloc(buf_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    draw_buf_2 = (uint8_t*)heap_caps_malloc(buf_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    
    if (!draw_buf_1 || !draw_buf_2) {
        Serial.println("LVGL buffer allocation failed!");
        return;
    }
    
    // Инициализация LVGL
    lv_init();
    
    // Создание дисплея
    display = lv_display_create(LCD_WIDTH, LCD_HEIGHT);
    lv_display_set_flush_cb(display, lv_port_disp_flush);
    lv_display_set_buffers(display, draw_buf_1, draw_buf_2, buf_size * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
    
    Serial.println("LVGL display initialized");
}

#pragma once

// LCD (ST7789V2)
#define LCD_DC    4
#define LCD_CS    5
#define LCD_SCK   6
#define LCD_MOSI  7
#define LCD_RST   8
#define LCD_BL    15
#define LCD_WIDTH  240
#define LCD_HEIGHT 280

// Touch (CST816T) — общая I2C-шина с IMU и RTC
#define IIC_SDA   11
#define IIC_SCL   10
#define TP_RST    13
#define TP_INT    14

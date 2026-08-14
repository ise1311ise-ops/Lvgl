/**
 * @file lv_conf.h
 * Configuration file for LVGL v9.2.0
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#define LV_CONF_INCLUDE_SIMPLE

/*====================
   COLOR SETTINGS
 *====================*/
#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 0

/*=========================
   MEMORY SETTINGS
 *=========================*/
#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (64U * 1024U)          /* 64KB для heap LVGL */
#define LV_MEM_ADDR 0x0
#define LV_MEM_BUF_MAX_NUM 16
#define LV_MEMCPY_MEMSET_STD 1

/*====================
   HAL SETTINGS
 *====================*/
#define LV_TICK_CUSTOM 1
#if LV_TICK_CUSTOM
    #define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
    #define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())
#endif

#define LV_USE_LOG 0
#define LV_USE_ASSERT_NULL 1
#define LV_USE_ASSERT_MALLOC 1

/*================
   OPERATING SYSTEM
 *================*/
#define LV_USE_OS LV_OS_NONE

/*=====================
   WIDGETS
 *=====================*/
#define LV_USE_ARC 1
#define LV_USE_BAR 1
#define LV_USE_BTN 1
#define LV_USE_BTNMATRIX 1
#define LV_USE_CANVAS 1
#define LV_USE_CHECKBOX 1
#define LV_USE_DROPDOWN 1
#define LV_USE_IMAGE 1
#define LV_USE_LABEL 1
#define LV_USE_LINE 1
#define LV_USE_ROLLER 1
#define LV_USE_SLIDER 1
#define LV_USE_SWITCH 1
#define LV_USE_TEXTAREA 1
#define LV_USE_TABLE 1

/*==================
   EXTRA COMPONENTS
 *==================*/
#define LV_USE_ANIMIMG 1
#define LV_USE_CALENDAR 1
#define LV_USE_CHART 1
#define LV_USE_MSGBOX 1
#define LV_USE_SPINBOX 1
#define LV_USE_SPINNER 1
#define LV_USE_TABVIEW 1
#define LV_USE_TILEVIEW 1
#define LV_USE_WIN 1

/*==================
   THEMES
 *==================*/
#define LV_USE_THEME_DEFAULT 1
#define LV_THEME_DEFAULT_DARK 0
#define LV_THEME_DEFAULT_GROW 1
#define LV_THEME_DEFAULT_TRANSITION_TIME 80

#define LV_USE_THEME_BASIC 1
#define LV_USE_THEME_MONO 1

/*==================
   FONT USAGE
 *==================*/
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_28 1
#define LV_FONT_MONTSERRAT_32 1
#define LV_FONT_MONTSERRAT_40 1

/*===================
   LVGL INTERNALS
 *===================*/
#define LV_USE_PERF_MONITOR 0
#define LV_USE_MEM_MONITOR 0

/*====================
   OPTIONAL FEATURES
 *====================*/
#define LV_USE_SNAPSHOT 0
#define LV_USE_MONKEY 0
#define LV_USE_GRIDNAV 0
#define LV_USE_FRAGMENT 0
#define LV_USE_IMGFONT 0
#define LV_USE_IME_PINYIN 0
#define LV_USE_FILE_EXPLORER 0
#define LV_USE_OBJ_PROPERTY 1
#define LV_USE_FLEX 1
#define LV_USE_GRID 1

#endif /* LV_CONF_H */

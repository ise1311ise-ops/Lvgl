// lv_port_touch.cpp
#include "lv_port_touch.h"
#include "pin_config.h"
#include <Wire.h>
#include "Arduino_DriveBus_Library.h"

// I2C шина
std::shared_ptr<Arduino_IIC_DriveBus> IIC_Bus = 
    std::make_shared<Arduino_HWIIC>(IIC_SDA, IIC_SCL, &Wire);

// Тачскрин
std::unique_ptr<Arduino_IIC> CST816T(new Arduino_CST816x(
    IIC_Bus, CST816T_DEVICE_ADDRESS, TP_RST, TP_INT, nullptr));

static lv_indev_t *touch_indev;
static int32_t last_x = 0;
static int32_t last_y = 0;
static bool last_pressed = false;

void lv_port_touch_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    static bool initialized = false;
    
    if (!initialized) {
        if (CST816T->begin(400000)) {
            CST816T->IIC_Write_Device_State(
                CST816T->Arduino_IIC_Touch::Device::TOUCH_DEVICE_INTERRUPT_MODE,
                CST816T->Arduino_IIC_Touch::Device_Mode::TOUCH_DEVICE_INTERRUPT_PERIODIC);
            initialized = true;
        }
    }
    
    if (initialized) {
        int32_t fingers = CST816T->IIC_Read_Device_Value(
            CST816T->Arduino_IIC_Touch::Value_Information::TOUCH_FINGER_NUMBER);
        
        if (fingers > 0) {
            int32_t x = CST816T->IIC_Read_Device_Value(
                CST816T->Arduino_IIC_Touch::Value_Information::TOUCH_X_POSITION);
            int32_t y = CST816T->IIC_Read_Device_Value(
                CST816T->Arduino_IIC_Touch::Value_Information::TOUCH_Y_POSITION);
            
            // CST816T возвращает координаты для повернутого экрана
            // При необходимости скорректируйте под вашу ориентацию
            last_x = x;
            last_y = y;
            last_pressed = true;
            
            data->state = LV_INDEV_STATE_PRESSED;
            data->point.x = last_x;
            data->point.y = last_y;
        } else {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void lv_port_touch_init(void)
{
    touch_indev = lv_indev_create();
    lv_indev_set_type(touch_indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(touch_indev, lv_port_touch_read);
}

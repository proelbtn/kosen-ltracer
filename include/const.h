#include "h8-3069/int.h"
#include "h8-3069/iodef.h"

#define FALSE 0
#define TRUE 1

#define UPPER 0
#define LOWER 1
#define LEFT 0
#define RIGHT 1

#define SENSOR_BUFFER_SIZE 16
#define SENSOR_BUFFER_SIZE_FILTER 0x0F

#define LCD_WIDTH 8
#define LCD_HEIGHT 2

#define INT_BASE_RESOLUTION (0x1000 - 0x1)
// lcd_handler is called every TIMER_INT_TIME0 * 0x400 = 16384[us] = 16.384[ms]
#define INT_LCD_CALL_CYCLE_FLAG (0x100 - 0x1)
// ad_handler is called every TIMER_INT_TIME0 * 0x1 = 64[us]
#define INT_AD_CALL_CYCLE_FLAG (0x1 - 0x1)
// motor_handler is called every TIMER_INT_TIME0 * 0x8= 512[us]
#define INT_MOTOR_CALL_CYCLE_FLAG (0x8 - 0x1)

// unit: 1[us]
// Addition / Subtraction can be called only 800 times in 64[us]
#define TIMER_INT_TIME0 64

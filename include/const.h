#ifndef __CONST_H__
#define __CONST_H__

#include "h8-3069/int.h"
#include "h8-3069/iodef.h"

typedef unsigned char bool;

#define FALSE 0
#define TRUE 1

#define BLACK FALSE
#define WHITE TRUE

#define UPPER 0
#define LOWER 1
#define LEFT 0
#define RIGHT 1

#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3

#define SENSOR_BUFFER_SIZE 16
#define SENSOR_BUFFER_SIZE_FILTER 0x0F

#define LCD_WIDTH 8
#define LCD_HEIGHT 2

// resolution is 256
#define INT_BASE_RESOLUTION (0x200 - 0x1)
// lcd_handler is called every TIMER_INT_TIME0 * 0x100 = 32768[us] = 32.768[ms]
#define INT_LCD_CALL_CYCLE_FLAG (0x100 - 0x1)
// ad_handler is called every TIMER_INT_TIME0 * 0x2 = 256[us]
#define INT_AD_CALL_CYCLE_FLAG (0x10 - 0x1)
// motor_handler is called every TIMER_INT_TIME0 * 0x4 = 512[us]
#define INT_MOTOR_CALL_CYCLE_FLAG (0x40 - 0x1)

// TODO: decide
#define SENSOR_THRESHOLD 180

// unit: 1[us]
// Addition / Subtraction can be called only 1600 times in 128[us]
#define TIMER_INT_TIME0 128

#endif

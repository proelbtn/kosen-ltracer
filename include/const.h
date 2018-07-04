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

// TODO: decide the time
// timer count: unit = 1[us]
#define TIMER_INT_TIME0 1000

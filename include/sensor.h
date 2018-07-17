#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "const.h"

#define SENSOR_INT_MASK 0x0

#define SENSOR_BATTELY 0
#define SENSOR_LEFT 1
#define SENSOR_RIGHT 2

#define SENSOR_THRESHOLD 180
#define SENSOR_BLACK FALSE
#define SENSOR_WHITE TRUE

void sensor_init();
void sensor_ad_handler();

unsigned char sensor_get_battery();
unsigned char sensor_get_left();
unsigned char sensor_get_right();

#endif
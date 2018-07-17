#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "const.h"

#define DISPLAY_LOWER 1
#define DISPLAY_UPPER 0

#define DISPLAY_INT_MASK 0x7F

void display_init();
void display_int_handler();

bool display_get_update_flag();
void display_reset_update_flag();

void display_update();

#endif
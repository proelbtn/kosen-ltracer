#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "const.h"

#define CONTROL_INT_MASK 0xF

void control_init();
void control_int_handler();

bool control_get_update_flag();
void control_reset_update_flag();

void control_update();

#endif
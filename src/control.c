#include "control.h"

#include "sensor.h"
#include "motor.h"

static bool control_update_flag;

void control_init() {
    control_update_flag = FALSE;
}

void control_int_handler() {
    control_update_flag = TRUE;
}

bool control_get_update_flag() {
    return control_update_flag;
}

void control_reset_update_flag() {
    control_update_flag = FALSE;
}

void control_update() {
    unsigned char battery = sensor_get_battery();
    bool left = sensor_get_left() < SENSOR_THRESHOLD;
    bool right = sensor_get_right() < SENSOR_THRESHOLD;

    if (left == SENSOR_BLACK && right == SENSOR_BLACK) motor_set_mode(MOTOR_FORWARD, MOTOR_BACKWARD); 
    if (left == SENSOR_WHITE && right == SENSOR_BLACK) motor_set_mode(MOTOR_BACKWARD, MOTOR_FORWARD); 
    if (left == SENSOR_BLACK && right == SENSOR_WHITE) motor_set_mode(MOTOR_FORWARD, MOTOR_FORWARD); 
    if (left == SENSOR_WHITE && right == SENSOR_WHITE) motor_set_mode(MOTOR_BACKWARD, MOTOR_FORWARD); 
}
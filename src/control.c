#include "control.h"
#include "display.h"
#include "sensor.h"
#include "motor.h"

// ===================================================================

static bool control_update_flag;

// ===================================================================

void control_init() {
    // 変数の初期化をする
    control_update_flag = FALSE;
}

void control_int_handler() {
    control_update_flag = TRUE;
}

// ===================================================================

bool control_get_update_flag() {
    return control_update_flag;
}

void control_update() {
    // 何かいろいろしている所
    unsigned char battery = sensor_get_battery();

    unsigned char lval = sensor_get_left();
    unsigned char rval = sensor_get_right();
    unsigned char bval = sensor_get_battery();

    display_hbuffer[0][0] = "0123456789ABCDEF"[(lval >> 4) % 16];
    display_hbuffer[0][1] = "0123456789ABCDEF"[lval % 16];
    display_hbuffer[0][6] = "0123456789ABCDEF"[(rval >> 4) % 16];
    display_hbuffer[0][7] = "0123456789ABCDEF"[rval % 16];
    display_hbuffer[1][3] = "0123456789ABCDEF"[(bval >> 4) % 16];
    display_hbuffer[1][4] = "0123456789ABCDEF"[bval % 16];

    bool left = sensor_get_left() < SENSOR_THRESHOLD;
    bool right = sensor_get_right() < SENSOR_THRESHOLD;

    if (left == SENSOR_BLACK && right == SENSOR_BLACK) motor_set_states(MOTOR_FORWARD, MOTOR_BACKWARD); 
    if (left == SENSOR_WHITE && right == SENSOR_BLACK) motor_set_states(MOTOR_BACKWARD, MOTOR_FORWARD); 
    if (left == SENSOR_BLACK && right == SENSOR_WHITE) motor_set_states(MOTOR_FORWARD, MOTOR_FORWARD); 
    if (left == SENSOR_WHITE && right == SENSOR_WHITE) motor_set_states(MOTOR_BACKWARD, MOTOR_FORWARD); 
}

void control_reset_update_flag() {
    control_update_flag = FALSE;
}

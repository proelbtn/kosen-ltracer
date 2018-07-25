#include "control.h"
#include "display.h"
#include "sensor.h"
#include "motor.h"

// ===================================================================

#define STATE_N 0
#define STATE_Lw 1
#define STATE_Ls 2
#define STATE_R 3

// ===================================================================

static bool control_update_flag;
static unsigned char state;
static int cnts[2][2];

// ===================================================================

void control_init() {
    // 変数の初期化をする
    control_update_flag = FALSE;
    state = STATE_N;

    cnts[SENSOR_BLACK][SENSOR_BLACK] = 0;
    cnts[SENSOR_BLACK][SENSOR_WHITE] = 0;
    cnts[SENSOR_WHITE][SENSOR_BLACK] = 0;
    cnts[SENSOR_WHITE][SENSOR_WHITE] = 0;
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
    unsigned char lval = sensor_get_left();
    unsigned char rval = sensor_get_right();
    unsigned char bval = sensor_get_battery();

    // 表示をしている部分

    bool left = lval < SENSOR_THRESHOLD;
    bool right = rval < SENSOR_THRESHOLD;

    display_hbuffer[0][0] = "BW"[right];
    display_hbuffer[0][7] = "BW"[left];
    display_hbuffer[1][0] = "0123456789ABCDEF"[(bval >> 4) % 16];
    display_hbuffer[1][1] = "0123456789ABCDEF"[bval % 16];
    display_hbuffer[1][7] = "0123"[state];

    switch (state) {
        case STATE_N:
            if (cnts[SENSOR_WHITE][SENSOR_WHITE] >= 1) state = STATE_Lw;
            else if (left == SENSOR_BLACK && right == SENSOR_BLACK) state = STATE_R;
            break;
        case STATE_Lw:
            if (cnts[SENSOR_BLACK][SENSOR_BLACK] >= 4) state = STATE_Ls;
            else if (cnts[SENSOR_BLACK][SENSOR_WHITE] >= 8) state = STATE_N;
            break;
        case STATE_Ls:
            if (!(left == SENSOR_BLACK && right == SENSOR_BLACK)) state = STATE_N;
            break;
        case STATE_R:
            if (cnts[SENSOR_BLACK][SENSOR_BLACK] >= 4) state = STATE_N;
            break;
    }

    if (left == SENSOR_BLACK && right == SENSOR_BLACK) {
        if (state == STATE_Ls) motor_set_states(MOTOR_BACKWARD, MOTOR_FORWARD);
        else motor_set_states(MOTOR_FORWARD, MOTOR_BACKWARD);
    }
    if (left == SENSOR_WHITE && right == SENSOR_BLACK) motor_set_states(MOTOR_BACKWARD, MOTOR_FORWARD); 
    if (left == SENSOR_BLACK && right == SENSOR_WHITE) motor_set_states(MOTOR_FORWARD, MOTOR_FORWARD); 
    if (left == SENSOR_WHITE && right == SENSOR_WHITE) motor_set_states(MOTOR_BACKWARD, MOTOR_FORWARD); 


    if (left == SENSOR_BLACK && right == SENSOR_BLACK) cnts[SENSOR_BLACK][SENSOR_BLACK]++;
    else cnts[SENSOR_BLACK][SENSOR_BLACK] = 0;
    if (left == SENSOR_BLACK && right == SENSOR_WHITE) cnts[SENSOR_BLACK][SENSOR_WHITE]++;
    else cnts[SENSOR_BLACK][SENSOR_WHITE] = 0;
    if (left == SENSOR_WHITE && right == SENSOR_BLACK) cnts[SENSOR_WHITE][SENSOR_BLACK]++;
    else cnts[SENSOR_WHITE][SENSOR_BLACK] = 0;
    if (left == SENSOR_WHITE && right == SENSOR_WHITE) cnts[SENSOR_WHITE][SENSOR_WHITE]++;
    else cnts[SENSOR_WHITE][SENSOR_WHITE] = 0;
}

void control_reset_update_flag() {
    control_update_flag = FALSE;
}

#include "const.h"
#include "motor.h"

unsigned char motor_prev_states[2];
unsigned char motor_now_states[2];

void motor_init() {
    PBDDR = 0x0F;
    motor_prev_states[MOTOR_LEFT] = MOTOR_STOP;
    motor_prev_states[MOTOR_RIGHT] = MOTOR_STOP;
    motor_now_states[MOTOR_LEFT] = MOTOR_STOP;
    motor_now_states[MOTOR_RIGHT] = MOTOR_STOP;
}

static void motor_change_mode(unsigned char left, unsigned char right) {
    unsigned char flag = 0x00;

    switch (left) {
        case MOTOR_STOP: flag |= 0x00; break;
        case MOTOR_FORWARD: flag |= 0x01; break;
        case MOTOR_BACKWARD: flag |= 0x02; break;
        case MOTOR_BRAKE: flag |= 0x03; break;
    }

    switch (right) {
        case MOTOR_STOP: flag |= 0x00; break;
        case MOTOR_FORWARD: flag |= 0x04; break;
        case MOTOR_BACKWARD: flag |= 0x08; break;
        case MOTOR_BRAKE: flag |= 0x0B; break;
    }

    PBDR = (PBDR & 0xF0) | flag;

}

void motor_int_handler() {
    if (motor_prev_states[MOTOR_LEFT] == motor_now_states[MOTOR_LEFT] && 
        motor_prev_states[MOTOR_RIGHT] == motor_now_states[MOTOR_RIGHT]) {
        motor_change_mode(motor_now_states[MOTOR_LEFT], motor_now_states[MOTOR_RIGHT]);
    }
    else {
        motor_change_mode(MOTOR_STOP, MOTOR_STOP);
        motor_prev_states[MOTOR_LEFT] = motor_now_states[MOTOR_LEFT];
        motor_prev_states[MOTOR_RIGHT] = motor_now_states[MOTOR_RIGHT];
    }
}

void motor_set_mode(unsigned char left, unsigned char right) {
    motor_now_states[MOTOR_LEFT] = left;
    motor_now_states[MOTOR_RIGHT] = right;
}
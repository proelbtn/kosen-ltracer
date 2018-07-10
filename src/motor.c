#include "motor.h"

void motor_init() {
    PBDDR = 0x0F;
}

void motor_set_mode_left(unsigned char mode) {
    switch (mode) {
        case STOP:
            PBDR = (PBDR & ~0x03) | 0x00;
            break;
        case FORWARD:
            PBDR = (PBDR & ~0x03) | 0x02;
            break;
        case BACKWARD:
            PBDR = (PBDR & ~0x03) | 0x01;
            break;
        case BRAKE:
            PBDR = (PBDR & ~0x03) | 0x03;
            break;
    }
}

void motor_set_mode_right(unsigned char mode) {
    switch (mode) {
        case STOP:
            PBDR = (PBDR & ~0x0B) | 0x00;
            break;
        case FORWARD:
            PBDR = (PBDR & ~0x0B) | 0x04;
            break;
        case BACKWARD:
            PBDR = (PBDR & ~0x0B) | 0x08;
            break;
        case BRAKE:
            PBDR = (PBDR & ~0x0B) | 0x0B;
            break;
    }
}
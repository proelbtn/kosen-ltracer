#include "motor.h"

void motor_init() {
    PBDDR = 0x0F;
}

void motor_set_mode_left(unsigned char mode) {
    switch (mode) {
        case STOP:
            P9DR = P9DR & ~0x03 | 0x00;
            break;
        case FORWARD:
            P9DR = P9DR & ~0x03 | 0x02;
            break;
        case BACKWARD:
            P9DR = P9DR & ~0x03 | 0x01;
            break;
        case BRAKE:
            P9DR = P9DR & ~0x03 | 0x03;
            break;
    }
}

void motor_set_mode_right(unsigned char mode) {
    switch (mode) {
        case STOP:
            P9DR = P9DR & ~0x03 | 0x00;
            break;
        case FORWARD:
            P9DR = P9DR & ~0x03 | 0x02;
            break;
        case BACKWARD:
            P9DR = P9DR & ~0x03 | 0x01;
            break;
        case BRAKE:
            P9DR = P9DR & ~0x03 | 0x03;
            break;
    }
}
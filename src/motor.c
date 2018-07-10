#include "const.h"
#include "motor.h"

void motor_init() {
    PBDDR = 0x0F;
}

void motor_set_mode(unsigned char left, unsigned char right) {
    unsigned char flag = 0x00;

    switch (left) {
        case STOP:
            flag |= 0x00;
            break;
        case FORWARD:
            flag |= 0x01;
            break;
        case BACKWARD:
            flag |= 0x02;
            break;
        case BRAKE:
            flag |= 0x03;
            break;
    }

    switch (right) {
        case STOP:
            flag |= 0x00;
            break;
        case FORWARD:
            flag |= 0x04;
            break;
        case BACKWARD:
            flag |= 0x08;
            break;
        case BRAKE:
            flag |= 0x0B;
            break;
    }

    PBDR = (PBDR & 0xF0) | flag;
}
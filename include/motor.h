#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_STOP 0
#define MOTOR_FORWARD 1
#define MOTOR_BACKWARD 2
#define MOTOR_BRAKE 3

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

#define MOTOR_INT_MASK 0x0

void motor_init();
void motor_int_handler();

void motor_set_mode(unsigned char left, unsigned char right);

#endif
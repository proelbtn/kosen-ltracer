#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "const.h"

// 割り込みの周期を決定する定数（タイマーを1分周する）
#define MOTOR_INT_MASK 0x0

// モーターの状態を設定する際に用いる定数
#define MOTOR_STOP 0
#define MOTOR_FORWARD 1
#define MOTOR_BACKWARD 2
#define MOTOR_BRAKE 3

// 初期化関数と割り込みハンドラ
void motor_init();
void motor_int_handler();

// 次の状態を設定する関数
void motor_set_state(unsigned char left, unsigned char right);

#endif
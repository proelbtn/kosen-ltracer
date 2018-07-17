#include "const.h"
#include "motor.h"

// ステートの配置を決める定数
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

// ===================================================================

// 状態のダブルバッファリングを行うための変数
// 貫通電流対策のためにわざわざダブルバッファリングしている
unsigned char motor_prev_states[2];
unsigned char motor_now_states[2];

// モータの制御を行う関数
static void motor_change_mode(unsigned char left, unsigned char right);

// ===================================================================

void motor_init() {
    // モーターの制御に必要なポートの設定をする
    PBDDR = 0x0F;

    // 変数の初期化をする
    motor_prev_states[MOTOR_LEFT] = MOTOR_STOP;
    motor_prev_states[MOTOR_RIGHT] = MOTOR_STOP;
    motor_now_states[MOTOR_LEFT] = MOTOR_STOP;
    motor_now_states[MOTOR_RIGHT] = MOTOR_STOP;
}

void motor_int_handler() {
    // もし、前回のモーターの状態と今回のモーターの状態が一緒なら
    // モーターをその状態にする（状態の更新は冗長なのでしていない）
    if (motor_prev_states[MOTOR_LEFT] == motor_now_states[MOTOR_LEFT] && 
        motor_prev_states[MOTOR_RIGHT] == motor_now_states[MOTOR_RIGHT]) {
        motor_change_mode(motor_now_states[MOTOR_LEFT], motor_now_states[MOTOR_RIGHT]);
    }

    // もし、前回のモーターの状態と今回のモーターの状態が異なるなら
    // モーターをMOTOR_STOP状態にする（貫通電流対策）
    // そして、古い状態を新しい状態で書き換える
    else {
        motor_change_mode(MOTOR_STOP, MOTOR_STOP);
        motor_prev_states[MOTOR_LEFT] = motor_now_states[MOTOR_LEFT];
        motor_prev_states[MOTOR_RIGHT] = motor_now_states[MOTOR_RIGHT];
    }
}

// ===================================================================

void motor_set_mode(unsigned char left, unsigned char right) {
    // 次の状態を設定する
    motor_now_states[MOTOR_LEFT] = left;
    motor_now_states[MOTOR_RIGHT] = right;
}

// ===================================================================

static void motor_change_mode(unsigned char left, unsigned char right) {
    // 与えられた状態に応じてフラグを設定し、それをポートに書き込んでいる
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
#include "control.h"
#include "display.h"
#include "motor.h"
#include "sensor.h"
#include "h8-3069/timer.h"

// ===================================================================

int main() {
    // ROMエミュレーションを有効にする
    ROMEMU();

    // 各パーツを初期化する
    control_init();
    // display_init();
    motor_init();
    sensor_init();

    // 割り込みの設定をする
    timer_init();
    timer_set(0, 128);
    timer_start(0);
    ENINT();
    

    while(TRUE) {
        // もしディスプレイ更新フラグが立っていたら、ディスプレイを更新する
        // if (display_get_update_flag()) {
        //     display_update();
        //     display_reset_update_flag();
        // }

        // もし制御更新フラグが立っていたら、制御情報を更新する
        if (control_get_update_flag()) {
            control_update();
            control_reset_update_flag();
        }
    }
}

// ===================================================================

#pragma interrupt
void int_imia0(void) {
    // ソフトウェアカウンタ
    static unsigned int scnt = 0;

    // 割り込み要因毎にカウンタを確認し、呼び出しが必要ならハンドラを呼び出す
    control_int_handler();
    // if ((scnt & DISPLAY_INT_MASK) == 0x0) display_int_handler();
    motor_int_handler();
    sensor_int_handler();

    scnt += 1;

    // 次の割り込みのための準備
    timer_intflag_reset(0);
    ENINT();
}

#pragma interrupt
void int_adi(void) {
    // センサのA/D変換のハンドラを呼び出す
    sensor_ad_handler();

    // 次の割り込みのための準備
    ENINT();
}

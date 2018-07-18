#include "sensor.h"
#include "h8-3069/ad.h"

// バッファの配置を決める定数
#define SENSOR_BATTERY 0
#define SENSOR_LEFT 1
#define SENSOR_RIGHT 2
#define SENSOR_NUM 3
#define SENSOR_BUFFER_SIZE 1

// ===================================================================

// 次に書き込まれるバッファの添字
static unsigned char sensor_buffer_ptr;

// センサーバッファ
static unsigned char sensor_buffer[SENSOR_NUM][SENSOR_BUFFER_SIZE];

// 和を保持しておくカウンタ（毎回、総和を求めるのは馬鹿らしいので）
static unsigned int sensor_total[SENSOR_NUM];

// ===================================================================

void sensor_init() {
    // A/D変換の初期化をする
    ad_init();

    // 変数の初期化をする
    sensor_buffer_ptr = 0;
    for (int i = 0; i < SENSOR_BUFFER_SIZE; i++) {
        sensor_buffer[SENSOR_BATTERY][i] = 0;
        sensor_buffer[SENSOR_LEFT][i] = 0;
        sensor_buffer[SENSOR_RIGHT][i] = 0;
    }
    sensor_total[SENSOR_BATTERY] = 0;
    sensor_total[SENSOR_LEFT] = 0;
    sensor_total[SENSOR_RIGHT] = 0;
}

void sensor_int_handler() {
    ad_scan(0, TRUE);
}

void sensor_ad_handler() {
    int temp;
    ad_stop();

    // センサーバッファの更新をする
    temp = sensor_buffer[SENSOR_BATTERY][sensor_buffer_ptr];
    sensor_buffer[SENSOR_BATTERY][sensor_buffer_ptr] = ADDRAH;
    sensor_total[SENSOR_BATTERY] += ADDRAH - temp;

    temp = sensor_buffer[SENSOR_LEFT][sensor_buffer_ptr];
    sensor_buffer[SENSOR_LEFT][sensor_buffer_ptr] = ADDRBH;
    sensor_total[SENSOR_LEFT] += ADDRBH - temp;

    temp = sensor_buffer[SENSOR_RIGHT][sensor_buffer_ptr];
    sensor_buffer[SENSOR_RIGHT][sensor_buffer_ptr] = ADDRCH;
    sensor_total[SENSOR_RIGHT] += ADDRCH - temp;
    
    // ポインタをインクリメントする
    sensor_buffer_ptr = (sensor_buffer_ptr + 1) % SENSOR_BUFFER_SIZE;
}

// ===================================================================

unsigned char sensor_get_battery() {
    // センサーから読んだ値の平均値を返す（厳密には平均値より少し小さい）
    return sensor_total[SENSOR_BATTERY] / SENSOR_BUFFER_SIZE;
}

unsigned char sensor_get_left() {
    // センサーから読んだ値の平均値を返す
    return sensor_total[SENSOR_LEFT] / SENSOR_BUFFER_SIZE;
}

unsigned char sensor_get_right() {
    // センサーから読んだ値の平均値を返す
    return sensor_total[SENSOR_RIGHT] / SENSOR_BUFFER_SIZE;
}

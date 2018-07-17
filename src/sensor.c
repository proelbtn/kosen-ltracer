#include "sensor.h"

#include "h8-3069/ad.h"

static unsigned char sensor_buffer_ptr;
static unsigned char sensor_buffer[3][16];
static unsigned int sensor_total[3];

void sensor_init() {
    // A/D変換の初期化をする
    ad_init();

    // 変数の初期化をする
    sensor_buffer_ptr = 0;
    for (int i = 0; i < 16; i++) {
        sensor_buffer[SENSOR_BATTELY][i] = 0;
        sensor_buffer[SENSOR_LEFT][i] = 0;
        sensor_buffer[SENSOR_RIGHT][i] = 0;
    }
    sensor_total[SENSOR_BATTELY] = 0;
    sensor_total[SENSOR_LEFT] = 0;
    sensor_total[SENSOR_RIGHT] = 0;
    
}

void sensor_ad_handler() {
    ad_stop();

    // センサーバッファの更新をする
    sensor_buffer[SENSOR_BATTELY][sensor_buffer_ptr] = ADDRAH; 
    sensor_total[SENSOR_BATTELY] += ADDRAH;
    sensor_total[SENSOR_BATTELY] -= sensor_buffer[SENSOR_BATTELY][(sensor_buffer_ptr + 1) % 16];
    
    sensor_buffer[SENSOR_LEFT][sensor_buffer_ptr] = ADDRBH; 
    sensor_total[SENSOR_LEFT] += ADDRAH;
    sensor_total[SENSOR_LEFT] -= sensor_buffer[SENSOR_LEFT][(sensor_buffer_ptr + 1) % 16];

    sensor_buffer[SENSOR_RIGHT][sensor_buffer_ptr] = ADDRCH; 
    sensor_total[SENSOR_RIGHT] += ADDRAH;
    sensor_total[SENSOR_RIGHT] -= sensor_buffer[SENSOR_RIGHT][(sensor_buffer_ptr + 1) % 16];

    sensor_buffer_ptr = (sensor_buffer_ptr + 1) & 0xF;
}

unsigned char sensor_get_battery() {
    return sensor_total[SENSOR_BATTELY] % 16;
}

unsigned char sensor_get_left() {
    return sensor_total[SENSOR_BATTELY] % 16;
}

unsigned char sensor_get_right() {
    return sensor_total[SENSOR_BATTELY] % 16;
}
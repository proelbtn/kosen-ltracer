#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "const.h"

// 割り込みの周期を決定する定数（タイマーを1分周する）
#define SENSOR_INT_MASK 0x0

// 白と黒の境界に利用すべき値とその色
// 仮にセンサーがvalという値を読んだとする
// この時、val < SENSOR_THRESHOLDがセンサーが読んだ色を示す
#define SENSOR_THRESHOLD 180
#define SENSOR_BLACK FALSE
#define SENSOR_WHITE TRUE

// 初期化関数と割り込みハンドラ
void sensor_init();
void sensor_ad_handler();

// 各センサーの値を取ってくる関数
unsigned char sensor_get_battery();
unsigned char sensor_get_left();
unsigned char sensor_get_right();

#endif

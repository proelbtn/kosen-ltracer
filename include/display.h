#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "const.h"

// 割り込みの周期を決定する定数（タイマーを128分周する）
#define DISPLAY_INT_MASK 0xFF

#define DISPLAY_LOWER 1
#define DISPLAY_UPPER 0

extern char display_hbuffer[2][8];

// 初期化関数と割り込みハンドラ
void display_init();
void display_int_handler();

// mainのイベントループに用いる関数たち
bool display_get_update_flag();
void display_update();
void display_reset_update_flag();

#endif

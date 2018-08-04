#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "const.h"

// 割り込みの周期を決定する定数（タイマーを16分周する）
#define CONTROL_INT_MASK 0x1

// 初期化関数と割り込みハンドラ
void control_init();
void control_int_handler();

// mainのイベントループに用いる関数たち
bool control_get_update_flag();
void control_update();
void control_reset_update_flag();

#endif

#include "display.h"
#include "h8-3069/lcd.h"

// ===================================================================

// ダブルバッファリング用のバッファ
char display_hbuffer[2][8];
static char display_lbuffer[2][8];

static bool display_update_flag;

// ===================================================================

void display_init() {
    // LCDを初期化する
    lcd_init();

    // 変数の初期化をする
    for (int x = 0; x < 8; x++) {
        display_hbuffer[DISPLAY_UPPER][x] = ' ';
        display_hbuffer[DISPLAY_LOWER][x] = ' ';
        display_lbuffer[DISPLAY_UPPER][x] = '\0';
        display_lbuffer[DISPLAY_LOWER][x] = '\0';
    }

    // ディスプレイを初期化する
    display_update();

    display_update_flag = FALSE;
}

void display_int_handler() {
    display_update_flag = TRUE;
}

// ===================================================================

bool display_get_update_flag() {
    return display_update_flag;
}

void display_update() {
    // 各文字について、ダブルバッファリングで書き込みを行う
    for (int x = 0; x < 8; x++) {
        if (display_lbuffer[DISPLAY_UPPER][x] != display_hbuffer[DISPLAY_UPPER][x]) {
            display_lbuffer[DISPLAY_UPPER][x] = display_hbuffer[DISPLAY_UPPER][x];
            lcd_cursor(x, DISPLAY_UPPER);
            lcd_printch(display_lbuffer[DISPLAY_UPPER][x]);
        }
        if (display_lbuffer[DISPLAY_LOWER][x] != display_hbuffer[DISPLAY_LOWER][x]) {
            display_lbuffer[DISPLAY_LOWER][x] = display_hbuffer[DISPLAY_LOWER][x];
            lcd_cursor(x, DISPLAY_LOWER);
            lcd_printch(display_lbuffer[DISPLAY_LOWER][x]);
        }
    }
}

void display_reset_update_flag() {
    display_update_flag = FALSE;
}

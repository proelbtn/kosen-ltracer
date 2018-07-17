#include "display.h"

#include "h8-3069/lcd.h"

static char display_hbuffer[2][8];
static char display_lbuffer[2][8];

static bool display_update_flag;

void display_init() {
    lcd_init();

    for (int x = 0; x < 8; x++) {
        display_hbuffer[DISPLAY_UPPER][x] = ' ';
        display_hbuffer[DISPLAY_LOWER][x] = ' ';
        display_lbuffer[DISPLAY_UPPER][x] = '\0';
        display_lbuffer[DISPLAY_LOWER][x] = '\0';
    }

    display_update();

    display_update_flag = FALSE;
}

void display_int_handler() {
    display_update_flag = TRUE;
}

bool display_get_update_flag() {
    return display_update_flag;
}

void display_reset_update_flag() {
    display_update_flag = FALSE;
}

void display_update() {
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
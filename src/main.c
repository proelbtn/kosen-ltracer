#include "h8-3069-int.h"
#include "h8-3069-iodef.h"
#include "ad.h"
#include "lcd.h"
#include "timer.h"

// =============================================================================

#define FALSE 0
#define TRUE 1

#define UPPER 0
#define LOWER 1
#define LEFT 0
#define RIGHT 1

#define LCD_WIDTH 8
#define LCD_HEIGHT 2

// TODO: decide the time
// timer count: unit = 1[us]
#define TIMER_INT_TIME0 1000

// =============================================================================

unsigned char ad_buffer[2][3];

unsigned char lcd_buffer[LCD_HEIGHT][LCD_WIDTH + 1];

// =============================================================================

int main(void);

void lcd_handler(void);

inline void lcd_ensure_eof(void);
inline void lcd_fill_out(unsigned char ch);
inline void lcd_buffer_clear();

// =============================================================================

int main() {
    // enable ROM emulation
    ROMEMU();

    // initialize A/D converter
    ad_init();

    // initialize lcd
    lcd_init();
    lcd_ensure_eof();

    // initialize timer
    timer_init();
    timer_set(0, TIMER_INT_TIME0);
    timer_start(0);

    // enable interrupt
    ENINT();

    while(1) {}
}

void lcd_handler(void) {
    lcd_ensure_eof();
    lcd_cursor(0, UPPER);
    lcd_printstr(lcd_buffer[UPPER]);
    lcd_cursor(0, LOWER);
    lcd_printstr(lcd_buffer[LOWER]);
}

#pragma interrupt
void int_imia0(void) {
    lcd_handler();

    timer_intflag_reset(0);
    ENINT();
}

#pragma interrupt
void int_adi(void) {
}

inline void lcd_ensure_eof(void) {
    lcd_buffer[UPPER][LCD_WIDTH] = lcd_buffer[LOWER][LCD_WIDTH] = '\0';
}

inline void lcd_fill_out(unsigned char ch) {
    for (int i = 0; i < LCD_WIDTH; i++) lcd_buffer[UPPER][i] = lcd_buffer[LOWER][i] = ch;
}

inline void lcd_buffer_clear() {
    lcd_fill_out(' ');
    lcd_ensure_eof();
}

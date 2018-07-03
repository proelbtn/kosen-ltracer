#include "const.h"

#include "ad.h"
#include "lcd.h"
#include "timer.h"

// =============================================================================

unsigned char lcd_buffer[LCD_HEIGHT][LCD_WIDTH + 1];
unsigned char lcd_update_flag;

unsigned char sensor_battery;
unsigned char sensor_buffer[2][3];
unsigned char sensor_buffer_ptr;

// =============================================================================

int main(void);

inline void lcd_handler(void);
inline void ad_handler(void);
inline void motor_handler(void);

inline void lcd_ensure_eof(void);
inline void lcd_fill_out(unsigned char ch);
inline void lcd_buffer_clear();

// =============================================================================

int main() {
    // 1. initialize step

    // enable ROM emulation
    ROMEMU();

    // initialize A/D converter
    ad_init();

    // initialize sensor
    sensor_battery = 0;
    for (int i = 0; i < SENSOR_BUFFER_SIZE; i++) sensor_buffer[LEFT][i] = sensor_buffer[RIGHT][i] = 0;

    // initialize lcd
    lcd_init();
    lcd_buffer_clear();
    lcd_update_flag = FALSE;

    // initialize timer
    timer_init();
    timer_set(0, TIMER_INT_TIME0);
    timer_start(0);

    // enable interrupt
    ENINT();
    
    while(TRUE) {
        if (lcd_update_flag) {
            lcd_ensure_eof();

            lcd_cursor(0, UPPER);
            lcd_printstr(lcd_buffer[UPPER]);
            lcd_cursor(0, LOWER);
            lcd_printstr(lcd_buffer[LOWER]);

            lcd_update_flag = FALSE;
        }
    }
}

// =============================================================================

inline void lcd_handler(void) {
    lcd_update_flag = TRUE;
}

inline void ad_handler(void) {
    ad_scan(0, TRUE);
}

inline void motor_handler(void) {
       
}

// =============================================================================

#pragma interrupt
void int_imia0(void) {
    lcd_handler();
    ad_handler();

    timer_intflag_reset(0);
    ENINT();
}

#pragma interrupt
void int_adi(void) {
    ad_stop();

    sensor_buffer_ptr = (sensor_buffer_ptr + 1) & 0x0F;

    sensor_battery = ADDRAH; 
    sensor_buffer[LEFT][sensor_buffer_ptr] = ADDRBH;
    sensor_buffer[RIGHT][sensor_buffer_ptr] = ADDRCH;

    ENINT();
}

// =============================================================================

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

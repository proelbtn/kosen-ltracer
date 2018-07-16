#include "const.h"

#include "ad.h"
#include "lcd.h"
#include "timer.h"
#include "motor.h"

// =============================================================================

unsigned char lcd_buffer[LCD_HEIGHT][LCD_WIDTH + 1];
volatile unsigned char lcd_update_flag;

volatile unsigned char sensor_battery;
volatile unsigned char sensor_buffer[2][SENSOR_BUFFER_SIZE];
volatile unsigned char sensor_buffer_ptr;

volatile unsigned char motor_update_flag;

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

    // port initialize
    P6DDR = 0x00;

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

    // initialize motor
    motor_init();
    motor_update_flag = FALSE;

    // enable interrupt
    ENINT();

    // until key is pressed, sleep this line
    while (P6DR & 0x03 != 0x03) lcd_update_flag = motor_update_flag = FALSE;
    
    bool flag = FALSE;
    bool fleft, fright;
    while(TRUE) {
        if (lcd_update_flag) {
            lcd_ensure_eof();

            lcd_cursor(0, UPPER);
            lcd_printstr(lcd_buffer[UPPER]);
            lcd_cursor(0, LOWER);
            lcd_printstr(lcd_buffer[LOWER]);

            lcd_update_flag = FALSE;
        }
        if (motor_update_flag) {
            bool left = SENSOR_THRESHOLD >= sensor_buffer[LEFT][sensor_buffer_ptr];
            bool right = SENSOR_THRESHOLD >= sensor_buffer[RIGHT][sensor_buffer_ptr];

            if (flag && (left != BLACK || right != WHITE)) {
                motor_update_flag = FALSE;
                continue;
            }

            if (left == WHITE && right == WHITE) motor_set_mode(BACKWARD, FORWARD);
            if (left == WHITE && right == BLACK) motor_set_mode(BACKWARD, FORWARD);
            if (left == BLACK && right == WHITE) motor_set_mode(FORWARD, FORWARD);
            if (left == BLACK && right == BLACK) motor_set_mode(FORWARD, BACKWARD);

            if (left != BLACK || right != WHITE) flag = TRUE;

            lcd_buffer[UPPER][0] = right == WHITE ? 'W' : 'B';
            lcd_buffer[UPPER][7] = left == WHITE ? 'W' : 'B';
            lcd_buffer[LOWER][3] = "0123456789ABCDEF"[(sensor_battery & 0xF0) >> 4];
            lcd_buffer[LOWER][4] = "0123456789ABCDEF"[sensor_battery & 0xF];

            motor_update_flag = FALSE;
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
    motor_update_flag = TRUE;
}

// =============================================================================

#pragma interrupt
void int_imia0(void) {
    static int scnt = 0;

    scnt = (scnt + 1) & INT_BASE_RESOLUTION;

    if (!(scnt & INT_LCD_CALL_CYCLE_FLAG)) lcd_handler();
    if (!(scnt & INT_AD_CALL_CYCLE_FLAG)) ad_handler();
    if (!(scnt & INT_MOTOR_CALL_CYCLE_FLAG)) motor_handler();

    timer_intflag_reset(0);
    ENINT();
}

#pragma interrupt
void int_adi(void) {
    ad_stop();

    sensor_buffer_ptr = (sensor_buffer_ptr + 1) & SENSOR_BUFFER_SIZE_FILTER;

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

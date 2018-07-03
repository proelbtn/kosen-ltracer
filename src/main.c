#include "h8-3069-int.h"
#include "h8-3069-iodef.h"
#include "timer.h"
#include "lcd.h"

// timer count: unit = 1[us]
const unsigned int timer0 = 3000;

// lcd buffer
unsigned char buffer[2][9];

// =============================================================================

void init(void);
int main(void);
void lcd_handler(void);

// =============================================================================

void init(void) {
    // enable ROM emulation
    ROMEMU();

    // initialize lcd
    lcd_init();

    // initialize timer
    timer_init();
    timer_set(0, timer0);
    timer_start(0);

    // enable interrupt
    ENINT();
}

int main() {
    init();

    int i;
    for (i = 0; i < 8; i++) {
        buffer[0][i] = i + '0';
        buffer[1][i] = i + 'A';
    }  

    while(1) {}
}

void lcd_handler(void) {
    buffer[0][8] = buffer[1][8] = '\0';
    lcd_cursor(0, 0);
    lcd_printstr(buffer[0]);
    lcd_cursor(0, 1);
    lcd_printstr(buffer[1]);
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

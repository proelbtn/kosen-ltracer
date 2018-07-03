#include "h8-3069-int.h"
#include "h8-3069-iodef.h"
#include "timer.h"

// timer count: unit = 1[us]
const unsigned int timer0 = 1000;

int main() {
    ROMEMU();

    timer_init();
    timer_set(0, timer0);
    timer_start(0);
    ENINT();
}

#pragma interrupt
void int_imia0(void) {
    timer_intflag_reset(0);
    ENINT();
}

#pragma interrupt
void int_adi(void) {
}

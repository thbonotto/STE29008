#include <avr/io.h>
#include <avr/interrupt.h>

#include "NTC.h"

int main(void) {
    int x;
    while(1) {
        Accumulate(x);
        RMS();
        Temperature();
    }
    return 0;
}


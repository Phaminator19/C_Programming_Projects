#include <msp430g2553.h>

unsigned int i = 0;

void main (void){

    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |=0x41;
    P1OUT &= 0xFC;

    for(;;)
    {
        for(i=1; i<= 20000; i++);
        P1OUT ^= 0x40;

        for(i=1; i<= 20000; i++);
        P1OUT ^= 0x41;
     }
}
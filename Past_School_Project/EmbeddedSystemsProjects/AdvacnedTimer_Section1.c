//Advanced Timer
// Video Demo: https://youtu.be/OfKZeiQpz_E

#include <msp430.h> 
#define redLED BIT0
#define greenLED BIT7


void config_ACLK_to_32KHz_crystal();


void config_ACLK_to_32KHz_crystal()
{
    // By default, ACLK runs on LFMODCLK at 5MHz/128 = 39 KHz
     // Reroute pins to LFXIN/LFXOUT functionality
    PJSEL1 &= ~BIT4;
    PJSEL0 |= BIT4;
    // Wait until the oscillator fault flags remain cleared
    CSCTL0 = CSKEY; // Unlock CS registers
    do {
        CSCTL5 &= ~LFXTOFFG; // Local fault flag
        SFRIFG1 &= ~OFIFG; // Global fault flag
    }while((CSCTL5 & LFXTOFFG) != 0);

    CSCTL0_H = 0; // Lock CS registers

    return;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;
	
	config_ACLK_to_32KHz_crystal();

	P1DIR |= redLED;
	P9DIR |= greenLED;
	P1OUT &= ~redLED;
	P9OUT &= ~greenLED;

	//configure channel 0
	TA0CCR0 = 3277-1;
	TA0CCTL0 |= CCIE;
	TA0CCTL0 &= ~CCIFG;

	//configure channel 1
	TA0CCR1 = 16384 - 1; //@32K * 0.5seconds = cycles
	TA0CCTL1 |= CCIE;
	TA0CCTL1 &= ~CCIFG;

	//configure timer (aclk) (divide by 1) (continuous mode)
	TA0CTL = TASSEL_1 | ID_0 | MC_2 | TACLR;

	//ACLK is active only and the rest of the clocks are inactive. This is the LPM for it.
	_low_power_mode_3();

	return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR() {
    P1OUT ^= redLED;
    TA0CCR0 += 3277;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void T0A1_ISR() {
    P9OUT ^= greenLED;
    TA0CCR1 += 16384;
    TA0CCTL1 &= ~CCIFG;
}

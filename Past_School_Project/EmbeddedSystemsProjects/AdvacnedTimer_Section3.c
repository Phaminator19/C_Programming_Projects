//Advanced Timer
//n this section I look up in the MSP430FR6989 Data sheet to directing the PWM signal to the LED
// Video Demo: https://youtu.be/OfKZeiQpz_E

#include <msp430.h> 
#define redLED BIT0
#define greenLED BIT7
#define PWM_PIN BIT0

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
	
	P1DIR |= PWM_PIN; //p1dir bit = 1
	P1SEL1 &= ~PWM_PIN; //P1SEL1 BIT = 0
	P1SEL0 |= PWM_PIN;      //P1SEL0 BIT = 1

	P1DIR |= redLED;
	P9DIR |= greenLED;
	P1OUT &= ~redLED;
	P9OUT &= ~greenLED;

    config_ACLK_to_32KHz_crystal();
	//configure channel 0
	TA0CCR0 = 33 -1; //@ 32 KHz --> 0.001 seconds (1000 Hz)

    //configure timer (ACLK) (divide by 1) (up mode)
	TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;

	//configuring channel 1 for PWM

	//OUTPUT PATTERN: RESET/SET
	TA0CCTL1 |= OUTMOD_7;

	//MODIFY THIS VALUE BELOW BETWEEN 0 AND 32 TO ADJUST THE BRIGHTNESS LEVEL;
	TA0CCR1 = 20;



	//ACLK is active only and the rest of the clocks are inactive. This is the LPM for it.
	for(;;) {}

	return 0;
}



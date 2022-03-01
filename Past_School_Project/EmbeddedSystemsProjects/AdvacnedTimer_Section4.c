//Advanced Timer
//in this section I modify the code from the previous section so that it would demo multiple brightness levels
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

	P9DIR |= greenLED;
	P9OUT &= ~greenLED; //turn the green LED off first

    config_ACLK_to_32KHz_crystal();
	//configure TIMER0 channel 0 does PWM
	TA0CCR0 = 33 - 1; //@ 32 KHz --> 0.001 seconds (1000 Hz)

    //configure timer (ACLK) (divide by 1) (up mode)
	TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;

    //OUTPUT PATTERN: RESET/SET
    TA0CCTL1 |= OUTMOD_7;
    TA0CCR1 = 0;

	//configure timer 1 channel 0 to generate the 1-second delay
	TA1CCR0 = 32768 - 1; //DELAY AT 1-SECOND INTERVAL 32K * 1 = # cycles;
	TA1CCTL0 = CCIE;
	TA1CCTL0 &= ~CCIFG;

	//configure timer1 (ACLK, Divide by 1, up mode)
	TA1CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;

    //ACLK is active only and the rest of the clocks are inactive. This is the LPM for it.
	_low_power_mode_3();
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void T1A0_ISR()
{
        P9OUT ^= greenLED;

        //MODIFY THIS VALUE BELOW BETWEEN 0 AND 32 TO ADJUST THE BRIGHTNESS LEVEL;
        if (TA0CCR1 >= 30) {
            TA0CCR1 = 0;
        }

        else {
            TA0CCR1 += 5;
        }

}




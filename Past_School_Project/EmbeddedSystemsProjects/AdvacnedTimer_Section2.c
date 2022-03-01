//Advanced Timer
// Video Demo: https://youtu.be/OfKZeiQpz_E

#include <msp430.h> 
#define redLED BIT0
#define greenLED BIT7


void config_ACLK_to_32KHz_crystal();

//A global variable to keep track of whether the LEDs are currently flashing or not
int status = 0;

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
	TA0CCR0 = 819 -1; //@ 8K * 0.1 seconds = # cycles
	TA0CCTL0 |= CCIE;
	TA0CCTL0 &= ~CCIFG;

	//configure channel 1
	TA0CCR1 = 4096 - 1; //@ 8K * 0.5seconds = # cycles
	TA0CCTL1 |= CCIE;
	TA0CCTL1 &= ~CCIFG;

	//configure channel 2
	TA0CCR2 = 32768 - 1; // @ 8k * 4 SECONDS = # cycles
	TA0CCTL2 |= CCIE;
	TA0CCTL2 &= ~CCIFG;


	//configure timer (ACLK) (divide by 4) (continuous mode)
	TA0CTL = TASSEL_1 | ID_2 | MC_2 | TACLR;

	//ACLK is active only and the rest of the clocks are inactive. This is the LPM for it.
	_low_power_mode_3();

	return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR() {
    P1OUT ^= redLED;
    TA0CCR0 += 819;

    //hardware clear the channel 0 interrupt flag itself no need to write the clear.
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void T0A1_ISR()
{
    if ((TA0CCTL1 & CCIFG) != 0)
    {
        P9OUT ^= greenLED;
        TA0CCR1 += 4096;
        TA0CCTL1 &= ~CCIFG;
    }

    if ((TA0CCTL2 & CCIFG) != 0)
        {
            if (status == 0)
            {
                //Both LEDs must be off
                P1OUT &= ~redLED;
                P9OUT &= ~greenLED;

                //disable ch. 0 and ch. 1 interrupt
                TA0CCTL0 &= ~CCIE;
                TA0CCTL1 &= ~CCIE;

                status = 1;
            }
            else if (status == 1)
            {
                //re-enable ch.0 and ch. 1 int
                TA0CCR0 = TA0R + 819;
                TA0CCTL0 |= CCIE;
                TA0CCTL0 &= ~CCIFG;

                TA0CCR1 = TA0R + 4096;
                TA0CCTL1 |= CCIE;
                TA0CCTL1 &= ~CCIFG;

                status = 0;
            }

            //RENEW THE CH2 BY 4 SEC
            TA0CCR2 += 32768;
            TA0CCTL2 &= ~CCIFG;
        }
}


#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //Turn off lowpower of FR5994


	TA0CTL = TASSEL_2 + MC_3 + ID_3; //SMCLK, UP/DOWN, divided by 8, 1MHz/8=125kHz
	TA0CCR0 = 10000; //Max TimerA reaches before coming down, so 12.5 Hz signal

	TA0CCTL1 = OUTMOD_4;
	TA0CCR1 = 10;
	TA0CCTL2 = OUTMOD_4;
	TA0CCR2 = 7500;

	P1DIR |= BIT0 + BIT1;
	P1SEL1 &= ~(BIT0 + BIT1);
	P1SEL0 |= BIT0 + BIT1;



	return 0;
}

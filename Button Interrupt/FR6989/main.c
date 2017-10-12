#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1IE |= BIT1;
    P1IFG &= ~BIT1;
    P1IES |= BIT1;

    __enable_interrupt();
	return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port1(void)
{
    P1OUT ^= BIT0;
    P1IFG &= ~BIT1;
    P1IES ^= BIT1;
}

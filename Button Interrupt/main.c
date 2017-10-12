#include <msp430.h> 


/**
 * main.c
 */

int blinking = 0x00; //boolean for whether we're blinking

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //Turn off lowpower of FR5994

	P1DIR |= BIT0; //Set P1.0 to output
	P1OUT &= ~BIT0; //set p1.0 to off

	P5DIR = 0x00;
	P5REN = 0x20;
	P5OUT = 0x20;
	P5IE |= BIT5; //enable interrupt on bit 3
	P5IFG &= ~BIT5; //clear flag
	
	__enable_interrupt(); //enables interrupts
	for(;;)
	{
	    P1OUT ^= blinking;
	    int i;
	    for(i=10000;i>0;i--){}
	}
}

#pragma vector = PORT5_VECTOR
__interrupt void Port_5(void) //interrupt for P5
{
    blinking ^=BIT0;
    P5IFG &= ~BIT5; //Clear flag
    P5IES ^= BIT5; //Toggle interrupt edge
}

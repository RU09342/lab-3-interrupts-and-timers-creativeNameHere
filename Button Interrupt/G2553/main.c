#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //initialize LED 1.0
    P1DIR |= BIT0;
    P1OUT &= ~(BIT0);

    //initialize 1.3 as an input pullup button
    P1DIR &=~BIT3;
    P1REN |=BIT3;
    P1OUT |=BIT3;
    P1IES |=BIT3;
    P1IE |= BIT3;
    P1IFG &= ~BIT3;

    __bis_SR_register(LPM0_bits + GIE);

    return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void ButtonInterrupt(void)
{
    P1OUT ^=BIT0;
    P1IES ^=BIT3;
    P1IFG &=~BIT3;
}

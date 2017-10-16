#include <msp430.h> 


/**
 * main.c
 */
unsigned int overflow = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;
    P1IE |= BIT3;
    P1IFG &= ~BIT3;

    TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR; //SMCLK, UP, divided by 1, 1MHz/8
    TA0CCTL0 = CCIE; //enable interrupt
    TA0CCR0 = 12500;
    TA1CTL = TASSEL_2 + MC_1 + ID_0 + TACLR;
    TA1CCR0 = 0;
    __bis_SR_register(GIE+LPM0_bits);

    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= BIT0;
}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(TA1CCR0 == 0)
    {
        overflow = 0;
        TA1CCR0 = 0xFFFF;
    }else{
        TA0CCR0 = (overflow*TA1CCR0)+TA1R;
        TA1CCR0 = 0;
        TA1CTL |= TACLR;
    }
    P1IFG &= ~BIT1;
    P1IES ^= BIT1;
}
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_A1(void)
{
    overflow = overflow +1;
}

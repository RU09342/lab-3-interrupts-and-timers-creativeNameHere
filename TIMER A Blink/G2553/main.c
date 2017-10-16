#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK, UP, divided by 8, 1MHz/8=125kHz
    TA0CCR0 = 10000; //Max TimerA reaches before coming down, so 12.5 Hz signal
    TA0CCR1 = 5000;
    TA0CCTL1 = CCIE;
    TA0CCTL0 = CCIE;




    P1DIR |= BIT0+BIT6;
    P1OUT &= ~(BIT0+BIT6);

    __bis_SR_register(LPM0_bits + GIE);

    return 0;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^=BIT6;
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^=BIT0;
}

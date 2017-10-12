#include <msp430.h> 


/**
 * main.c
 */
unsigned int overflow = 0;
unsigned int pressTime;
int pressed = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //Turn off lowpower of FR5994

    TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK, UP, divided by 8, 1MHz/8=125kHz
    TA0CCTL0 = CCIE;
    TA0CCR0 = 6250; //Max TimerA reaches before coming down, so 20 Hz signal

    P1DIR |= BIT0; //Set P1.0 to output
    P1OUT &= ~BIT0; //set p1.0 to off

    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1IE |= BIT1; //enable interrupt on bit 3
    P1IFG &= ~BIT1; //clear flag

    __enable_interrupt();

    while(1){}

    return 0;
}

//overflow interrupt
#pragma vector= TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    overflow = overflow + 1;
    P1OUT ^= 0x01;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) //interrupt for button
{
    if(pressed == 0)
    {
        overflow = 0;
        pressTime = TA0R;
        pressed = 1;
    }else{
        unsigned int depressTime = TA0R;
        TA0CCR0 = ((depressTime + overflow*TA0CCR0) - pressTime); //breaks down when this >65k, aka >0.5 seconds
        pressed = 0;
    }

    P1IFG &= ~BIT1; //Clear flag
    P1IES ^= BIT1; //Toggle interrupt edge
}

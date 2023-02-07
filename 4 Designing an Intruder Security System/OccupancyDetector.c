/*
 * OccupancyDetector.c
 *
 *  Created on: 2/2/2023
 *      Author: Jimmy Galeno
 */

#include <msp430.h>


void gpioInit();

int main(void){

    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer

    gpioInit();                             // Initialize all GPIO Pins for the project


    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    int count_1 = 0;                        // count_1 is 0



    while(1){

        if(~P4IN & BIT1) {                  // When button held red LED blinks and green LED is off
            P1OUT ^= BIT0;
            P6OUT &= ~BIT6;

            __delay_cycles(500000);         // Delay for 500000*(1/MCLK)= around .5 s


            count_1++;

            if(count_1 == 10){                // count reaches 10 sec, solid red LED
                P1OUT ^= BIT0;

                count_1 = 0;
                break;

            }


        }


        if(P4IN & BIT1) {                   // When button not held green LED blinks and red LED is off
            P6OUT ^= BIT6;
            P1OUT &= ~BIT0;

            __delay_cycles(3000000);        // Delay for 3000000*(1/MCLK)= 3 s
        }


    }
}

void gpioInit()
{
   // Setting Directions of Pins

       P1DIR |= BIT0;              // Configure P1.0 to an Output
       P6DIR |= BIT6;              // Configure P6.6 to an Output
       P4DIR &= ~BIT1;             // Configure P4.1 to an Input

       P4REN |= BIT1;               // Enable Resistor on P4.1
       P4OUT |= BIT1;               // Configure Resistor on P4.1 to be Pullup

}



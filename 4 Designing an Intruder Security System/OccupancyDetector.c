/*
 * OccupancyDetector.c
 *
 *  Created on: 2/2/2023
 *      Author: Jimmy Galeno
 */

#include <msp430.h>
#define armed 0                             // case when green LED blinks
#define warning 1                           // case when red LED blinks
#define alert 2                             // case when red LED is on


void gpioInit();

int main(void){

    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer

    gpioInit();                             // Initialize all GPIO Pins for the project


    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    int count_1 = 0;                        // count_1 is 0

    char state = armed;




    while(1){

        switch (state) {

        case armed:

            if(P4IN & BIT1) {                   // When button not held green LED blinks and red LED is off
                P6OUT ^= BIT6;
                P1OUT &= ~BIT0;

                __delay_cycles(3000000);        // Delay for 3000000*(1/MCLK)= 3 s

                count_1 = 0;                    // count reset to 0
               }
            else{
                state = warning;                // if not move to next case
            }


        break;

        case warning:

            if((~P4IN & BIT1)){                  // When button is held red LED blinks and green LED is off
                P1OUT ^= BIT0;
                P6OUT &= ~BIT6;

                __delay_cycles(100000);         // Delay for 100000*(1/MCLK)= around .5 s


                count_1++;                      // count starts incrementing
            }
            if((~P4IN & BIT1) && count_1 == 20){                // When button is pressed and count = 20 move to alert case
                state = alert;
            }
            if(P4IN & BIT1){                                    // When button is not pressed go back to the armed case
                state = armed;
            }

            break;

        case alert:

            if(~P2IN & BIT3){                   // if button 2.3 is pressed move to armed case
                state = armed;
            }
            else {
                P1OUT ^= BIT0;                  // red LED stays on while green LED is off
            }
            break;
     }
   }
}




void gpioInit()
{
   // Setting Directions of Pins

       P1DIR |= BIT0;              // Configure P1.0 to an Output
       P6DIR |= BIT6;              // Configure P6.6 to an Output
       P4DIR &= ~BIT1;             // Configure P4.1 to an Input
       P2DIR &= ~BIT3;             // Configure P2.3 to an Input

       P4REN |= BIT1;               // Enable Resistor on P4.1
       P4OUT |= BIT1;               // Configure Resistor on P4.1 to be Pullup
       P2REN |= BIT3;               // Enable Resistor on P2.3
       P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

}



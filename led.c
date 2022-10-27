//------------------------------------------------------------------------------
//
//  Description: This is the led.c file where the function definitions and
// declarations used for turning on the display go
//
//  Mohamed Mohamed-Ali
//  September 14 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "macros.h"
#include  "functions.h"
#include  "msp430.h"

extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;


void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}

void Carlson_StateMachine(void){
    switch(Time_Sequence){
      case 250:                        //
        if(one_time){
          Init_LEDs();
          //lcd_BIG_mid();
          display_changed = 1;
          one_time = 0;
        }
        Time_Sequence = 0;             //
        break;
      case 200:                        //
        if(one_time){
          P6OUT |= GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 150:                         //
        if(one_time){
          //P1OUT |= RED_LED;            // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = 0;
        }
        break;
      case 100:                         //
        if(one_time){
//          lcd_4line();
          lcd_BIG_bot();
          P6OUT |= GRN_LED;            // Change State of LED 5
          display_changed = 1;
          one_time = 0;
        }
        break;
      case  50:                        //
        if(one_time){
         // P1OUT &= ~RED_LED;           // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = 0;
        }
        break;                         //
      default: break;
    }
}
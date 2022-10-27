//------------------------------------------------------------------------------
//
//  Description: This is the switches.c file where the processes for switch 1
// and switch 2 go
//
//  Mohamed Mohamed-Ali
//  September 27 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

extern char display_line[4][11];
extern char event;
extern int checkswitch1;
extern int checkswitch2;
int okay_to_look_at_switch1;
int okay_to_look_at_switch2;
int sw1_position;
int sw2_position;
int count_debounce_SW1;
int count_debounce_SW2;
char temp_event;
char shapes [3]={CIRCLE,FIGURE_8,TRIANGLE}; 
int shapes_index = 0;
//signed int wait_to_run = -1;
int waiting;
char functs[4] = {RIGHT_FORWARD, RIGHT_REVERSE, LEFT_FORWARD, LEFT_REVERSE};
extern volatile unsigned int debounce_count1;
extern volatile unsigned int debounce_count2;
extern volatile unsigned char display_changed;


//------------------------------------------------------------------------------
void Switches_Process(void){
//------------------------------------------------------------------------------
// This function calls the individual Switch Functions
//------------------------------------------------------------------------------
Switch1_Process();
Switch2_Process();
}

//------------------------------------------------------------------------------
void Switch1_Process(void){
  //------------------------------------------------------------------------------
  // Switch 1 Configurations
  //------------------------------------------------------------------------------
  if (okay_to_look_at_switch1 && sw1_position){
    if (!(P4IN & SW1)){
      sw1_position = PRESSED;
      okay_to_look_at_switch1 = NOT_OKAY;
      count_debounce_SW1 = DEBOUNCE_RESTART;
      checkswitch1++;
      //debounce_count1 = 0;
     /* wait_to_run++;
      if(wait_to_run < 4){
        switch(functs[wait_to_run]){
        case RIGHT_FORWARD:
          strcpy(display_line[0], "  RIGHT   ");
          strcpy(display_line[1], "  MOTOR   ");
          strcpy(display_line[2], " FORWARD  ");
          break;
        case RIGHT_REVERSE:
          strcpy(display_line[0], "  RIGHT   ");
          strcpy(display_line[1], "  MOTOR   ");
          strcpy(display_line[2], " REVERSE  ");
          strcpy(display_line[3], "   OFF    ");
          break;
        case LEFT_FORWARD:
          strcpy(display_line[0], "   LEFT   ");
          strcpy(display_line[1], "  MOTOR   ");
          strcpy(display_line[2], "  FORWARD ");
          strcpy(display_line[3], "   OFF    ");
          break;
         case LEFT_REVERSE:
          strcpy(display_line[0], "   LEFT   ");
          strcpy(display_line[1], "  MOTOR   ");
          strcpy(display_line[2], " REVERSE  ");
          strcpy(display_line[3], "   OFF    ");
          break;
        }
      }   
      else{
        wait_to_run = 0;

        strcpy(display_line[0], "  RIGHT   ");
        strcpy(display_line[1], "  MOTOR   ");
        strcpy(display_line[2], " FORWARD  ");
        strcpy(display_line[3], "   OFF    ");
        
      }
    }
  }
      
      if(shapes_index < 2){
       shapes_index++; 
      }
      else{
       shapes_index = 0;
      }
      switch(shapes[shapes_index]){
      case CIRCLE:
        temp_event = CIRCLE;
        strcpy(display_line[0], "   PICK   ");
        strcpy(display_line[1], "  SHAPE:  ");
        strcpy(display_line[2], "  CIRCLE  ");
        strcpy(display_line[3], "          ");
        break;
      case FIGURE_8:
        temp_event = FIGURE_8;
        strcpy(display_line[0], "   PICK   ");
        strcpy(display_line[1], "  SHAPE:  ");
        strcpy(display_line[2], " FIGURE 8 ");
        strcpy(display_line[3], "          ");
        break;
      case TRIANGLE:
        temp_event = TRIANGLE;
        strcpy(display_line[0], "   PICK   ");
        strcpy(display_line[1], "  SHAPE:  ");
        strcpy(display_line[2], " TRIANGLE ");
        strcpy(display_line[3], "          ");
        break;
      default: break;
      
      }
      
      // do what you want with button press
*/
    }

  }

  if (count_debounce_SW1 <= DEBOUNCE_TIME){
    count_debounce_SW1++;
  }else{
    okay_to_look_at_switch1 = OKAY;
    if (P4IN & SW1){
      sw1_position = RELEASED;
    }
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void Switch2_Process(void){
  //------------------------------------------------------------------------------
  // Switch 2 Configurations
  //------------------------------------------------------------------------------
  if (okay_to_look_at_switch2 && sw2_position){
    if (!(P2IN & SW2)){
      sw2_position = PRESSED;
      checkswitch2++;
      debounce_count2 = 0;
      okay_to_look_at_switch2 = NOT_OKAY;
      count_debounce_SW2 = DEBOUNCE_RESTART;
      /*if(waiting){              // If waiting and switch is pressed
        waiting = 0;
        strcpy(display_line[3], "    ON    ");
        event = functs[wait_to_run];
      }
      else{
        event = 'W';
        waiting = 1;
        strcpy(display_line[3], "   OFF    ");
      }
   }
  }
      */
      //event = FIGURE_8;
      //event = temp_event;
      // do what you want with button press
    }
  }

  if (count_debounce_SW2 <= DEBOUNCE_TIME){
    count_debounce_SW2++;
  }else{
    okay_to_look_at_switch2 = OKAY;
    if (P2IN & SW2){
      sw2_position = RELEASED;
    }
  }
}

void Switch1Display(void){
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], " SWITCH 1 "); 
  display_changed = TRUE;
}

void Switch2Display(void){
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], " SWITCH 2 "); 
  display_changed = TRUE;
}

void BlackLineCheck(void){
  strcpy(display_line[2], "BLACK LINE");
  strcpy(display_line[3], " DETECTED ");
  display_changed = INITIAL;
}

void Switch3Display(void){
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], "          ");

  display_changed = TRUE;
}

void Switch4Display(void){
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], "          ");

  display_changed = TRUE;
}
//------------------------------------------------------------------------------
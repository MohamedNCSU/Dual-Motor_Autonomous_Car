//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

// Function Prototypes
//void main(void);



// Global Variables
int right_motor_count;
int left_motor_count;
char state = WAIT;
volatile char slow_input_down;
unsigned char display_mode;
extern volatile unsigned int update_display_count;
unsigned int test_value;
unsigned int Last_Time_Sequence;
unsigned int cycle_time;
unsigned int time_change;
char chosen_direction;
char change;
char event = NONE;
int checkswitch1 = 0;
int checkswitch2 = 0;
int delay_start;
int segment_count;
volatile int CIRCLE_TRAVEL_DIST = 2;
extern char display_line[4][11];
//extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern volatile unsigned int debounce_count1 = 0;
extern volatile unsigned int debounce_count2 = 0;
unsigned int blink_count=0;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
volatile unsigned int detect = 0;
volatile unsigned int linecounter = 0;
volatile unsigned int detect1 = 0;
volatile unsigned int linecounter1 = 0;
volatile unsigned int detect2 = 0;
volatile unsigned int linecounter2 = 0;
unsigned int pwmcheck = 0;
//extern volatile char one_time;

void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //
  //------------------------------------------------------------------------------
  PM5CTL0 &= ~LOCKLPM5;
  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                        // Initialize Clock System
  Init_Timer_B0();
  Init_Timer_B3();
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_LCD();                           // Initialize LCD
  Init_ADC();
  Init_Timer_B1();
  
  Switch4Display();
  
  
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    Switches_Process();                // Check for switch state change
    Display_Process();                 // Update Display
    P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
    
    if(!pwmcheck){
    if((ADC_Left_Detect > BLACKLINE) || (ADC_Right_Detect > BLACKLINE)){
      BlackLineCheck();
      
    }
    else if ((ADC_Left_Detect < BLACKLINE) && (ADC_Right_Detect < BLACKLINE)){
      Switch3Display();
    }
    }
    
    if(checkswitch1){
      pwmcheck++;
      Follow_Line();
    }
  }
}







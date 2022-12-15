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

// Global Variables
int right_motor_count;
int left_motor_count;
char state=WAIT;
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
int checkswitch1 = RESET_STATE;
int checkswitch2 = RESET_STATE;
int delay_start;
int segment_count;
volatile int CIRCLE_TRAVEL_DIST = TWOWHEEL;
extern char display_line[QUAD][SIZEDISPLAY];
extern volatile unsigned char display_changed;
extern volatile unsigned int debounce_count2;
unsigned int blink_count=RESET_STATE;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
volatile unsigned int detect = RESET_STATE;
volatile unsigned int linecounter = RESET_STATE;
volatile unsigned int detect1 = RESET_STATE;
volatile unsigned int linecounter1 = RESET_STATE;
volatile unsigned int detect2 = RESET_STATE;
volatile unsigned int linecounter2 = RESET_STATE;
unsigned int pwmcheck = RESET_STATE;
char UCspeed;
extern volatile unsigned int transmission;
volatile int update;
extern char PC_2_IOT[LARGE_RING_SIZE];
extern char PC_TEMP[SIZEDISPLAY1];
extern char IOT_2_PC[LARGE_RING_SIZE];
volatile unsigned int TXcheck = RESET_STATE;
volatile unsigned int ready = RESET_STATE;
extern unsigned int rdcmd;
extern unsigned int A1temp;
extern volatile unsigned int TXA0;
extern volatile unsigned int iotcma;
extern volatile unsigned int iotcmb;
extern volatile unsigned int iotcmc;
extern volatile unsigned int iotcmd;
extern volatile unsigned int debounce_count11;
extern volatile unsigned int debounce_count3;
extern volatile unsigned int debounce_count4;
extern volatile unsigned int debounce_count5;
extern volatile unsigned int startup;
extern volatile unsigned int SSID;
extern volatile unsigned int IPC;
extern volatile unsigned int parse;
extern unsigned int temp;
unsigned int pctemp;
extern unsigned int blackline;
extern unsigned int sevenprime;
extern volatile char prime;
extern unsigned int cr;
int timercheck;
extern volatile unsigned int detect3;
extern volatile unsigned int linecounter3;
unsigned int seconds;
unsigned int value;
extern unsigned int curver;
extern unsigned int curvel;
int flagid;
volatile int displayflag;
extern volatile unsigned int displaytime;


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

 
  
  Init_Serial_UCA0('a');
  Init_Serial_UCA1('a');
  Init_Timer_B1();
  Init_Timer_B2();
  
  strcpy(display_line[0], " WAITING  ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], "          ");
  
  display_changed = TRUE;
  
  
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    Display_Process();                 // Update Display
    P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
    
    
    if(TXA0){
      TXA0 = RESET_STATE;
      Find_CommandA0();
    }
    
    if(TXcheck){
      TXcheck = RESET_STATE;
      Find_Command();
    }
    
    if(rdcmd){
      rdcmd = RESET_STATE;
      Check_Command();
    }
    
    if((SSID)){
      Send_IOT();
    }
    
    
    if(debounce_count2 > THMS){
      P3OUT |= IOT_EN_CPU;
    }
    
    if(parse){
      for(int i = 0; i<LARGE_RING_SIZE; i++){
        if((IOT_2_PC[i] == '"')){
          if(IOT_2_PC[i+1] == '1'){
            pctemp = i;
            Parse_IP();
          }
        }
      }
    }
    
    if(blackline){
      Follow_Line();
    }
    
    
    if(curver){
      curver = RESET_STATE;
      CurveRight();
    }
    
    if(curvel){
      curvel = RESET_STATE;
      CurveLeft();
    }
    
    if(sevenprime){
      prime = 'A';
      Seven();
    }
    
    if(displaytime >= FIFTYMSINTERVAL){
      
      seconds = linecounter3 / FIFTYMSINTERVAL;
      HEXtoBCD(seconds);
      adc_line(THMS,FIFTHPOS);
      displaytime = RESET_STATE;
    }
    
    if(iotcma){
      Adjust_Left();
    }
    
    if(iotcmc){
      Adjust_Right();
    }
    
  }
}







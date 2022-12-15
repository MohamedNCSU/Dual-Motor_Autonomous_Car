//------------------------------------------------------------------------------
//
//  Description: This is the wheels.c files where all the functions for going
// in a circle, figure 8, and triangle go
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

extern char state;
extern unsigned int Last_Time_Sequence;
extern unsigned int cycle_time;
extern unsigned int time_change;
extern int right_motor_count;
extern int left_motor_count;
extern char event;
extern int delay_start;
extern int segment_count;
extern int figure8_count;
extern int triangle_count;
extern int rreverse;
extern int rforward;
extern int lreverse;
extern int lforward;
extern volatile unsigned int debounce_count11;
extern volatile unsigned int debounce_count3;
extern volatile unsigned int debounce_count4;
extern volatile unsigned int debounce_count5;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int detect;
extern volatile unsigned int linecounter;
extern volatile unsigned int detect1;
extern volatile unsigned int linecounter1;
extern volatile unsigned int detect2;
extern volatile unsigned int linecounter2;
extern volatile unsigned int detect4;
extern volatile unsigned int linecounter4;
extern volatile unsigned int detect6;
extern volatile unsigned int linecounter6;
extern volatile unsigned int detect7;
extern volatile unsigned int linecounter7;
extern unsigned int pwmcheck;
extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern volatile unsigned int iotcma;
extern volatile unsigned int iotcmb;
extern volatile unsigned int iotcmc;
extern volatile unsigned int iotcmd;
extern unsigned int done;
volatile char prime;
extern volatile unsigned int detect5;
extern volatile unsigned int linecounter5;

void Follow_Line(void){
  switch(state){
  case WAIT: 
    wait_case();
    break; 
  case START: 
    start_case();
    strcpy(display_line[0], "INTERCEPT ");
    display_changed = INITIAL;
    break; 
  case TRAVEL:
    black_travel();
    break;
  case NEXTTRAVEL:
    next_travel();
    break;
  case CIRCLE:
    black_circle();
    strcpy(display_line[0], "BL TRAVEL ");
    display_changed = INITIAL;
    break;
  case NEXTCIRCLE:
    next_circle();
    strcpy(display_line[0], "BL CIRCLE ");
    display_changed = INITIAL;
    break;
  case END:
    end_case();
    break;
  default:break;
  
  }
  
}

void Seven(void){
  switch(prime){
  case 'A':
    iotcma++;
    break;
  case 'D':
    iotcmd++;
    break;
  case 'P':
    iotcma=RESET_STATE;
    iotcmb=RESET_STATE;
    iotcmc=RESET_STATE;
    iotcmd=RESET_STATE;
    debounce_count11=RESET_STATE;
    debounce_count3=RESET_STATE;
    debounce_count4=RESET_STATE;
    debounce_count5=RESET_STATE;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    break;
  default: break;
  }
}

void wait_case(void){
  detect1++;
  strcpy(display_line[0], " BL TURN  ");
  display_changed = INITIAL;
  switch(linecounter1){
  case RESET_STATE:
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    break;
  case FIVESEC:
    LEFT_FORWARD_SPEED = TURNFAST;
    RIGHT_REVERSE_SPEED = TURNFAST;
    break;
  case FIVEF:
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    break;
  case SSEC3:
    strcpy(display_line[0], "INTERCEPT ");
    display_changed = INITIAL;
    RIGHT_FORWARD_SPEED = WHEEL_ON;
    LEFT_FORWARD_SPEED = WHEEL_ON;
    break;
  case EE:
    state = START;
    break;
  }
}

void start_case(void){
  RIGHT_FORWARD_SPEED = RIGHT_ON;
  LEFT_FORWARD_SPEED = LEFT_ON;
  
  if((ADC_Left_Detect >= BLACKLINE) || (ADC_Right_Detect >= BLACKLINE)){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    linecounter1 = RESET_STATE;
    state = CIRCLE;
  }
}

void inch_forward(void){
  switch(linecounter1){
  case RESET_STATE:
    if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect < BLACKLINEWHEEL)){
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_FORWARD_SPEED = BC; // prev 3590 both
    }
    else if((ADC_Right_Detect < BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)) {
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = BC;
    }
    else if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)){
      LEFT_FORWARD_SPEED = BC;
      RIGHT_FORWARD_SPEED = BC;
    }
    break;
    break;
  case O5:
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    break;
  case SSEC5:
    state = TRAVEL;
    break;
  default: break;
  }
  
}

void turn_line(void){
  if((ADC_Right_Detect < BLACKLINE)){
    LEFT_FORWARD_SPEED = BC;
    RIGHT_REVERSE_SPEED = BC;
  }
  else if(ADC_Right_Detect >= BLACKLINE){
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    state = CIRCLE;
  }
  else if((ADC_Left_Detect >= BLACKLINE)){
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    state = CIRCLE;
  }
  
}

void black_travel(void){
  P6OUT |= GRN_LED;
  detect6++;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  
  
  if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect < BLACKLINEWHEEL)){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = BC; // prev 3590 both
  }
  else if((ADC_Right_Detect < BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)) {
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = BC;
  }
  else if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)){
    LEFT_FORWARD_SPEED = BC;
    RIGHT_FORWARD_SPEED = BC;
  }
  
  /*if(linecounter6 > 50){
  state = NEXTTRAVEL;
}*/
  
  
}

void next_travel(void){
  detect7++;
  strcpy(display_line[0], "BL TRAVEL ");
  display_changed = INITIAL;
  if(linecounter7 <=FIVESEC){
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
  }
  
  else{
    state = CIRCLE;
  }
}

void black_circle(void){
  P1OUT |= RED_LED;
  detect5++;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  strcpy(display_line[0], "BL TRAVEL ");
  display_changed = INITIAL;
  
  
  /*if(linecounter5 >= 40) && (linecounter5 < 90){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}*/
  
  if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect < BLACKLINEWHEEL)){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = BC; // prev 3590 both
  }
  else if((ADC_Right_Detect < BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)) {
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = BC;
  }
  else if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)){
    LEFT_FORWARD_SPEED = BC;
    RIGHT_FORWARD_SPEED = BC;
  }
  
  /*if(linecounter5 >= 80){
  state = NEXTCIRCLE;
  detect++;
}*/
  
}

void next_circle(void){
  detect++;
  if(linecounter <=FIVESEC){
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
  }
  
  else{
    if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect < BLACKLINEWHEEL)){
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_FORWARD_SPEED = BC; // prev 3590 both
    }
    else if((ADC_Right_Detect < BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)) {
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = BC;
    }
    else if((ADC_Right_Detect >= BLACKLINEWHEEL) && (ADC_Left_Detect >= BLACKLINEWHEEL)){
      LEFT_FORWARD_SPEED = BC;
      RIGHT_FORWARD_SPEED = BC;
    }
  }
  
}

void end_case(void){
  detect2++;
  switch(linecounter2){
  case RESET_STATE:     
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    strcpy(display_line[0], " BL EXIT  ");
    display_changed = INITIAL;
    break;
  case FIVESEC: 
    RIGHT_FORWARD_SPEED = TK;
    LEFT_FORWARD_SPEED = TK;
    break;
  case SEVSEC: 
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    strcpy(display_line[0], " BL STOP  ");
    display_changed = INITIAL;
    break;
  default: break;
  }
}

void CurveRight(void){
  RIGHT_FORWARD_SPEED = CR;
  LEFT_FORWARD_SPEED = CS;
}

void CurveLeft(void){
  RIGHT_FORWARD_SPEED = CS;
  LEFT_FORWARD_SPEED = CR;
}


void Adjust_Left(void){
  switch(debounce_count11){
  case RESET_STATE:
    LEFT_FORWARD_SPEED = LF;
    RIGHT_REVERSE_SPEED = RF;
    break;
  case TWOWHEEL:
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    break;
  default: break;
  }
  
}

void Adjust_Right(void){
  switch(debounce_count4){
  case RESET_STATE:
    LEFT_REVERSE_SPEED = LF;
    RIGHT_FORWARD_SPEED = RF;
    break;
  case TWOWHEEL:
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    break;
  default: break;
  }
  
}
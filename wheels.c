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
//extern volatile char state;
extern char event;
extern int delay_start;
extern int segment_count;
extern int figure8_count = 0;
extern int triangle_count = 0;
extern int rreverse = 0;
extern int rforward = 0;
extern int lreverse = 0;
extern int lforward = 0;
extern volatile unsigned int debounce_count1;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int detect;
extern volatile unsigned int linecounter;
extern volatile unsigned int detect1;
extern volatile unsigned int linecounter1;
extern volatile unsigned int detect2;
extern volatile unsigned int linecounter2;
extern unsigned int pwmcheck;
extern char display_line[4][11];
extern volatile unsigned char display_changed;

void Follow_Line(void){
  switch(state){
  case WAIT: 
    wait_case();
    break; 
  case START: 
    start_case();
    strcpy(display_line[2], "INTERCEPT ");
    display_changed = INITIAL;
    break; 
  case STOP:
    inch_forward();
    strcpy(display_line[2], " WAITING  ");
    display_changed = INITIAL;
    break;
  case TURN:
    turn_line();
    strcpy(display_line[2], " TURNING  ");
    display_changed = INITIAL;
    break;
  case CIRCLE:
    black_circle();
    strcpy(display_line[2], " CIRCLING ");
    display_changed = INITIAL;
    break;
  case END:
    end_case();
    break;
  default:break;
  
  }
  
}

void wait_case(void){
  if(pwmcheck){
    state = START;
    Switch3Display();
  }
}

void start_case(void){
  RIGHT_FORWARD_SPEED = RIGHT_ON;
  LEFT_FORWARD_SPEED = LEFT_ON;
  detect1++;
  if((ADC_Left_Detect >= BLACKLINE) || (ADC_Right_Detect >= BLACKLINE)){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    state = STOP;
  }
}

void inch_forward(void){
  detect++;
  switch(linecounter){
  case 30:
    LEFT_FORWARD_SPEED = WHEEL_ON;
    RIGHT_REVERSE_SPEED = WHEEL_ON;
    break;
  case 37:
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    state = TURN;
    break;
  default: break;
  }
  
}

void turn_line(void){
  if((ADC_Right_Detect < BLACKLINE)){
    LEFT_FORWARD_SPEED = 3600;
    RIGHT_REVERSE_SPEED = 3600;
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

void black_circle(void){
  P1OUT |= RED_LED;
  RIGHT_REVERSE_SPEED = 0;
  if(ADC_Right_Detect >= BLACKLINEWHEEL){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = 3590;
  }
  else{
    LEFT_FORWARD_SPEED = 0;
    RIGHT_FORWARD_SPEED = 3590;
  }
  if(linecounter1 > 2000){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    strcpy(display_line[2], " STOPPED  ");
    display_changed = INITIAL;
    state = END;
  }
}

void end_case(void){
  detect2++;
  P6OUT |= LCD_BACKLITE;
  switch(linecounter2){
  case 30:     
    LEFT_FORWARD_SPEED = 5000;
    RIGHT_REVERSE_SPEED = 5000;
    strcpy(display_line[2], "INTERCEPT ");
    display_changed = INITIAL;
    break;
  case 37: 
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    break;
  case 39: 
    RIGHT_FORWARD_SPEED = 4000;
    LEFT_FORWARD_SPEED = 4000;
    break;
  case 60:
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    strcpy(display_line[2], " STOPPED  ");
    display_changed = INITIAL;
    break;
  default: break;
  }
}
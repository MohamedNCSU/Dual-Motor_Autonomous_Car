//------------------------------------------------------------------------------
//
//  Description: This is the interrupts c file where all the interrupts needed to run
//  functions, switches, and timers go
//  Mohamed Mohamed-Ali
//  October 5 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
volatile unsigned int debounce_count11;
volatile unsigned int debounce_count2;
extern volatile unsigned char update_display;
extern int checkswitch1;
extern int checkswitch2;
extern unsigned int blink_count;
extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern volatile unsigned int detect;
extern volatile unsigned int linecounter;
extern volatile unsigned int detect1;
extern volatile unsigned int linecounter1;
extern volatile unsigned int detect2;
extern volatile unsigned int linecounter2;
volatile unsigned int detect3;
volatile unsigned int linecounter3;
char IOT_2_PC[LARGE_RING_SIZE]; 
char PC_2_IOT[LARGE_RING_SIZE]; 
char PC_TEMP[10];
unsigned int temp;
volatile unsigned int usb_rx_wr;
volatile unsigned int direct_usb;
volatile unsigned int iot_rx_rd;
volatile unsigned int iot_rx_wr;
volatile unsigned int transmission;
extern volatile int update;
extern volatile unsigned int TXcheck;
extern volatile unsigned int ready;
volatile unsigned int temp2;
unsigned int direct_iot;
unsigned int A1temp;
unsigned int dcheck;
volatile char tempA1;
volatile unsigned TXA0;
volatile char tempA0;
volatile unsigned int iotcma;
volatile unsigned int iotcmb;
volatile unsigned int iotcmc;
volatile unsigned int iotcmd;
volatile unsigned int debounce_count3;
volatile unsigned int debounce_count4;
volatile unsigned int debounce_count5;
volatile unsigned int debounce_count6;
volatile unsigned int startup;
extern volatile unsigned int check1;
extern volatile unsigned int check2;
volatile unsigned int SSID;
volatile unsigned int parse;
volatile unsigned int IPC;
volatile unsigned int index;
extern unsigned int blackline;
extern unsigned int intercept;
volatile unsigned int icounter;
extern volatile char prime;
volatile unsigned int detect4;
volatile unsigned int linecounter4;
volatile unsigned int detect5;
volatile unsigned int linecounter5;
extern int timercheck;
volatile unsigned int displaytime;
extern volatile int displayflag;
volatile unsigned int detect6;
volatile unsigned int linecounter6;
volatile unsigned int detect7;
volatile unsigned int linecounter7;

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerB0 0 Interrupt handler
  //-----------------------------------------------------------------------------
  TB0CCTL0 &= ~CCIFG; 
  
  if(iotcma){
    debounce_count11++;
  }
  /*
  if(debounce_count11 >=20){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}
  */
  
  debounce_count2++;
  
  if(iotcmb){
    debounce_count3++;
  }
  
  switch(debounce_count3){
  case 3:
    RIGHT_REVERSE_SPEED = WHEEL_ON;
    LEFT_REVERSE_SPEED = WHEEL_ON;
    break;
    
  case 13:
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    break;
    
  default:break;
  }
  
  if(iotcmc){
    debounce_count4++;
  }
  /*
  switch(debounce_count4){
case 3:
  RIGHT_FORWARD_SPEED = WHEEL_ON;
  LEFT_REVERSE_SPEED = WHEEL_ON;
  break;
case 13:
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  break;
  
  default: break;
}
  */
  
  /* if(iotcmd){
  debounce_count5++;
}
  
  switch(debounce_count5){
case 20:
  LEFT_REVERSE_SPEED = 9000;
  RIGHT_FORWARD_SPEED = 9000;
  break;
  
case 26:
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  
  break;
  default:break;
}
  */
  
  if(startup){
    debounce_count6++;
  }
  
  switch(debounce_count6){
  case THSEC:
    strncpy(PC_2_IOT, "AT+CIPMUX=1\r\n",13);
    UCA0IE |= UCTXIE; // Enable Tx interrupt
    break;
  case THSEC1:
    UCA0IE &= ~UCTXIE;
    break;
  case SSEC1:
    strncpy(PC_2_IOT, "AT+CIPSERVER=1,8389\r\n",22);
    check2++;
    UCA0IE |= UCTXIE;
    break;
  case SSEC2:
    UCA0IE &= ~UCTXIE;
    break;
  case NSEC2:
    strncpy(PC_2_IOT, "AT+CWJAP?\r\n",12);
    UCA0IE |= UCTXIE;
    break;
  case NSEC3:
    UCA0IE &= ~UCTXIE;
    break;
  case O23:
    strncpy(PC_2_IOT, "AT+CIFSR\r\n",11);
    UCA0IE |= UCTXIE;
    
    break;
  case O24:
    UCA0IE &= ~UCTXIE;
    break;
  case O33:
    parse++;
    break;
    
  default:break;
  }
  
  
  
  
  //----------------------------------------------------------------------------
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
  //----------------------------------------------------------------------------
  TB0CCTL1 &= ~CCIFG; 
  update_display = INITIAL;
  //----------------------------------------------------------------------------
}


#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerB1 0 Interrupt handler
  //----------------------------------------------------------------------------
  
  TB1CCTL0 &= ~CCIFG;
  
  
  if(detect){
    linecounter++;
  }
  
  if(detect1){
    linecounter1++;
  }
  
  if(detect2){
    linecounter2++;
  }
  
  if(detect4){
    linecounter4++;
  }
  
  if(detect5){
    linecounter5++;
  }
  
  /*if(detect3){
  linecounter3++;
  seconds = linecounter3 % 10;
  HEXtoBCD(seconds);
  adc_line(3,6);
}
  */
  
  
  /*if(intercept){
  icounter++;
  RIGHT_FORWARD_SPEED = 5000;
  LEFT_FORWARD_SPEED = 5000;
}
  
  if(icounter>20){
  blackline++;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}
  
  
  if(prime == 'P'){
  detect3++;
  if(linecounter3>=20){
  prime = 'A';
  
}
}
  */
  
  
  
  //----------------------------------------------------------------------------
}

#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
  //----------------------------------------------------------------------------
  TB1CCTL1 &= ~CCIFG; 
  update_display = INITIAL;
  //----------------------------------------------------------------------------
}

#pragma vector = TIMER2_B0_VECTOR
__interrupt void Timer2_B0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerB1 0 Interrupt handler
  //----------------------------------------------------------------------------
  
  TB2CCTL0 &= ~CCIFG;
  if(detect3){
    linecounter3++;
    displaytime++;
  }
  
  if(detect6){
    linecounter6++;
  }
  
  if(detect7){
    linecounter7++;
  }
  
  
  //----------------------------------------------------------------------------
}

#pragma vector=TIMER2_B1_VECTOR
__interrupt void TIMER2_B1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
  //----------------------------------------------------------------------------
  TB2CCTL1 &= ~CCIFG; 
  update_display = INITIAL;
  //----------------------------------------------------------------------------
}

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  //-----------------------------------------------------------------------------
  // Echo back RXed character, confirm TX buffer is ready first
  switch(__even_in_range(UCA0IV,0x08)){
  case 0: break; // Vector 0 - no interrupt
  case 2:{ // Vector 2 - RXIFG
    temp = iot_rx_wr++;
    IOT_2_PC[temp] = UCA0RXBUF;
    //IOT_2_PC[temp] = tempA0; // Rx -> IOT_2_PC character array
    
    if(IOT_2_PC[temp] == '\n'){
      TXA0 = INITIAL;
    }
    
    if(IOT_2_PC[temp] == 'G'){
      startup = INITIAL;
    }
    
    if(IOT_2_PC[temp] == '"'){
      SSID = INITIAL;
    }    
    
    
    
    if (iot_rx_wr >= (sizeof(IOT_2_PC))){
      iot_rx_wr = BEGINNING; // Circular buffer back to beginning
    }
    
    UCA1IE |= UCTXIE; // Enable Tx interrupt
  }
  break;
  
  case 4:{ // Vector 4 - TXIFG
    
    if(PC_2_IOT[direct_iot] == '^'){
      UCA0IE &= ~UCTXIE;
    }
    
    
    UCA0TXBUF = PC_2_IOT[direct_iot++];
    
    if (direct_iot >= (sizeof(PC_2_IOT))){
      direct_iot = BEGINNING;
    }
    if (direct_iot == usb_rx_wr){
      UCA0IE &= ~UCTXIE; // Disable TX interrupt
    }
  }
  break;
  
  default: break;
  }
  //------------------------------------------------------------------------------
}

#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  //------------------------------------------------------------------------------
  // Echo back RXed character, confirm TX buffer is ready first
  switch(__even_in_range(UCA1IV,0x08)){
  case 0: break; // Vector 0 - no interrupt
  case 2:{ // Vector 2 - RXIFG
    temp = usb_rx_wr++;
    PC_2_IOT[temp] = UCA1RXBUF; // Rx -> PC_2_IOT character array
    
    if(PC_2_IOT[temp] == '\n'){
      TXcheck = INITIAL;
    }
    
    
    
    if (usb_rx_wr >= (sizeof(PC_2_IOT))){
      usb_rx_wr = BEGINNING; // Circular buffer back to beginning
    }
    UCA0IE |= UCTXIE; // Enable Tx interrupt
  }
  break;
  
  case 4:{ // Vector 4 - TXIFG
    
    tempA1 = IOT_2_PC[direct_usb++];
    
    UCA1TXBUF = tempA1;
    
    
    if (direct_usb >= (sizeof(IOT_2_PC))){
      direct_usb = BEGINNING; // Circular buffer back to beginning
    }
    
    unsigned int temp1 = direct_usb;
    if (temp1 == iot_rx_wr){
      UCA1IE &= ~UCTXIE; // Disable TX interrupt
    }
    
  }
  break;
  
  default: break;
  }
  //------------------------------------------------------------------------------
}

#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  // Switch 1
  if(P4IN & SW1){
    if (P4IFG & SW1) {
      P4IFG &= ~SW1; // IFG SW1 cleared
      P2IN &= ~SW2;
      startup=RESET_STATE;
      debounce_count6=RESET_STATE;
    }
  }
}


#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  // Switch 2
  if (P2IN & SW2){
    if (P2IFG & SW2) {
      P2IFG &= ~SW2; // IFG SW2 cleared
      P4IN &= ~SW1;
    }
  }
}



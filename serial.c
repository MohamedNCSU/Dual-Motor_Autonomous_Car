//------------------------------------------------------------------------------
//
//  Description: This is the serial.c file where all functions required to implement
//  serial communications go
// 
//  Mohamed Mohamed-Ali
//  November 14 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

extern volatile unsigned int iot_rx_wr;
extern volatile unsigned int usb_rx_wr;
unsigned int tempiot;
unsigned int tempc;
unsigned int cmdcheck;
unsigned int cmdcheck1;
unsigned int rdcmd;
unsigned int rdready;
extern char PC_2_IOT[LARGE_RING_SIZE];
extern char IOT_2_PC[LARGE_RING_SIZE];
char CMD_IOT[LARGE_RING_SIZE];
extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern volatile char tempA1;
extern unsigned int A1temp;
extern volatile unsigned int iotcma;
extern volatile unsigned int iotcmb;
extern volatile unsigned int iotcmc;
extern volatile unsigned int iotcmd;
unsigned int done;
extern volatile unsigned int debounce_count11;
extern volatile unsigned int debounce_count3;
extern volatile unsigned int debounce_count4;
extern volatile unsigned int debounce_count5;
extern volatile unsigned int debounce_count6;
extern volatile unsigned int startup;
volatile unsigned int check1;
volatile unsigned int check2;
extern volatile unsigned int parse;
unsigned int id1;
char address[2][11];
unsigned int index1;
unsigned int tempindex;
int z;
int y=INITIAL;
int l;
int h;
extern unsigned int pctemp;
unsigned int blackline;
unsigned int intercept;
unsigned int sevenprime;
unsigned int cr;
extern volatile unsigned int detect1;
extern volatile unsigned int detect3;
extern volatile unsigned int linecounter1;
extern volatile unsigned int detect;
extern volatile unsigned int linecounter;
extern volatile unsigned int detect2;
extern volatile unsigned int linecounter2;
extern volatile unsigned int detect4;
extern volatile unsigned int linecounter4;
extern volatile unsigned int detect5;
extern volatile unsigned int linecounter5;
extern volatile unsigned int detect6;
extern volatile unsigned int linecounter6;
extern volatile unsigned int detect7;
extern volatile unsigned int linecounter7;
extern char state;
unsigned int curver;
unsigned int curvel;
extern volatile unsigned int SSID;
extern int flagid;
extern unsigned int seconds;
unsigned int checkadc;


void Init_Serial_UCA0(char speed){
  //------------------------------------------------------------------------------
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
  // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
  //------------------------------------------------------------------------------
  // Configure eUSCI_A0 for UART mode
  UCA0CTLW0 = RESET_STATE;
  UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA0CTLW0 &= ~UCPEN; // No Parity
  UCA0CTLW0 &= ~UCSYNC;
  UCA0CTLW0 &= ~UC7BIT;
  UCA0CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  if (speed == 'a'){
    UCA0BRW = QUAD ; // 115,200 baud
    UCA0MCTLW = 0x5551 ;
  }
  else if(speed == 'b'){
    UCA0BRW = BUCOS16 ; 
    UCA0MCTLW = 0x4A00 ; 
  }
  else if(speed == 'c'){
    UCA0BRW = CUCOS16 ; 
    UCA0MCTLW = 0x4911 ;
  }
  else{
    UCA0BRW = QUAD ; // 115,200 baud
    UCA0MCTLW = 0x5551 ;
  }
  UCA0CTLW0 &= ~UCSWRST ; // release from reset
  UCA0TXBUF = 0x00; // Prime the Pump
  UCA0IE |= UCRXIE; // Enable RX interrupt
  //------------------------------------------------------------------------------
}

void Init_Serial_UCA1(char speed){
  //------------------------------------------------------------------------------
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
  // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
  //------------------------------------------------------------------------------
  // Configure eUSCI_A0 for UART mode
  UCA1CTLW0 = 0;
  UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA1CTLW0 &= ~UCPEN; // No Parity
  UCA1CTLW0 &= ~UCSYNC;
  UCA1CTLW0 &= ~UC7BIT;
  UCA1CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  if (speed == 'a'){
    UCA1BRW = QUAD ; // 115,200 baud
    UCA1MCTLW = 0x5551 ;
  }
  else if(speed == 'b'){
    UCA1BRW = BUCOS16 ; 
    UCA1MCTLW = 0x4A00 ; 
  }
  else{
    UCA1BRW = QUAD ; // 115,200 baud
    UCA1MCTLW = 0x5551 ;
  }
  UCA1CTLW0 &= ~UCSWRST ; // release from reset
  UCA1TXBUF = 0x00; // Prime the Pump
  UCA1IE |= UCRXIE; // Enable RX interrupt
  //------------------------------------------------------------------------------
}

void Find_Command(void){
  tempiot = iot_rx_wr;
  tempc = RESET_STATE;
  
  for(int i = RESET_STATE; i < LARGE_RING_SIZE; i++){
    
    if(tempiot >= LARGE_RING_SIZE){
      tempiot = RESET_STATE;
    }
    
    if(PC_2_IOT[tempiot] == '^'){
      
      cmdcheck = INITIAL;
    }
    
    if(PC_2_IOT[tempiot] == '\r'){
      PC_2_IOT[tempiot] = '\0';
      PC_2_IOT[tempiot+1] = '\0';
      cmdcheck = RESET_STATE;
    }
    
    if(cmdcheck){
      CMD_IOT[tempc++] = PC_2_IOT[tempiot];
      
      PC_2_IOT[tempiot] = '\0';
      
      rdcmd = INITIAL;
    }
    tempiot++;
  }
}

void Find_CommandA0(void){
  tempiot = usb_rx_wr;
  tempc = RESET_STATE;
  
  for(int i = RESET_STATE; i < LARGE_RING_SIZE; i++){
    
    if(tempiot >= LARGE_RING_SIZE){
      tempiot = RESET_STATE;
    }
    
    if(IOT_2_PC[tempiot] == '^'){
      
      cmdcheck = INITIAL;
    }
    
    if(IOT_2_PC[tempiot] == '\r'){
      IOT_2_PC[tempiot] = '\0';
      IOT_2_PC[tempiot+1] = '\0';
      cmdcheck = RESET_STATE;
    }
    
    if(cmdcheck){
      CMD_IOT[tempc++] = IOT_2_PC[tempiot];
      
      IOT_2_PC[tempiot] = '\0';
      
      rdcmd = INITIAL;
    }
    tempiot++;
  }
}

void Check_Command(void){
  
  for(int i = RESET_STATE; i < LARGE_RING_SIZE; i++){
    
    if((tempc >= LARGE_RING_SIZE)){
      tempc = RESET_STATE;
    }
    
    if(rdready){
      flagid++;
      detect3++;
      switch(CMD_IOT[tempc]) {
      case '%' :
        //P6OUT |= LCD_BACKLITE;
        RIGHT_FORWARD_SPEED = FASTWHEEL;
        LEFT_FORWARD_SPEED = FASTWHEEL;
        
        display_line[THMS][RESET_STATE] = 'F';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        break;
      case 'S' :
        RIGHT_FORWARD_SPEED = SLOWWHEEL;
        LEFT_FORWARD_SPEED = SLOWWHEEL;
        display_line[THMS][RESET_STATE] = 'S';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        break;
      case 'R' :
        curver++;
        display_line[THMS][RESET_STATE] = 'R';
        display_changed = INITIAL;
        break;
      case 'L' :
        curvel++;
        display_line[THMS][RESET_STATE] = 'L';
        display_changed = INITIAL;
        break;
      case 'r' :
        iotcmc++;
        break;
      case 'l' :
        iotcma++;
        break;
      case 'G':
        strcpy(display_line[THMS], " GREEN ON ");
        display_changed = INITIAL;
        P6OUT |= GRN_LED;
        //done = 1;
        break;
      case 'g':
        strcpy(display_line[3], "GREEN OFF ");
        display_changed = INITIAL;
        P6OUT &= ~GRN_LED;
        // done = 1;
        break;
        /* case 'A':
        iotcma++;
        strcpy(display_line[3], " STRAIGHT ");
        display_changed = INITIAL;
        break;
        */
      case 'B':
        iotcmb++;
        display_line[3][0] = 'B';
        display_changed = INITIAL;
        break;
        
        /*case 'C' :
        iotcmc++;
        strcpy(display_line[3], "   TURN   ");
        display_changed = INITIAL;
        break;
        */
        /*case 'D':
        iotcmd++;
        display_line[3][0] = 'D';
        display_changed = INITIAL;
        break;
        */
      case '*':
        P6OUT |= LCD_BACKLITE;
        blackline++;
        checkadc++;
        ADC_Check();
        strncpy(display_line[3], "Auto",QUAD);
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        cr = RESET_STATE;
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
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        curvel = RESET_STATE;
        curver = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        display_line[3][0] = 'P';
        display_changed = INITIAL;
        break;
        
      case '/':
        //cr++;
        //P6OUT |= LCD_BACKLITE;
        
        RIGHT_FORWARD_SPEED = INTERCEPTWHEEL;
        LEFT_FORWARD_SPEED = INTERCEPTWHEEL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        strcpy(display_line[0], " BL START ");
        strncpy(display_line[3], "Auto",4);
        display_changed = INITIAL;
        break;
        
      case 'X':
        state = END;
        break;
        
      case '1':
        strcpy(display_line[0], "ARRIVED 01");
        display_line[3][0] = '1';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
        
      case '2':
        strcpy(display_line[0], "ARRIVED 02");
        display_line[3][0] = '2';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
        
      case '3':
        strcpy(display_line[0], "ARRIVED 03");
        display_line[3][0] = '3';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
        
      case 'V':
        strcpy(display_line[0], "ARRIVED 04");
        display_line[3][0] = '4';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
        
      case '5':
        strcpy(display_line[0], "ARRIVED 05");
        display_line[3][0] = '5';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
        
      case '6':
        strcpy(display_line[0], "ARRIVED 06");
        display_line[3][0] = '6';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
        
      case '7':
        strcpy(display_line[0], "ARRIVED 07");
        display_line[3][0] = '7';
        display_changed = INITIAL;
        iotcma=RESET_STATE;
        iotcmb=RESET_STATE;
        iotcmc=RESET_STATE;
        iotcmd=RESET_STATE;
        debounce_count11=RESET_STATE;
        debounce_count3=RESET_STATE;
        debounce_count4=RESET_STATE;
        debounce_count5=RESET_STATE;
        detect = RESET_STATE;
        linecounter = RESET_STATE;
        detect1 = RESET_STATE;
        linecounter1 = RESET_STATE;
        detect2 = RESET_STATE;
        linecounter2 = RESET_STATE;
        detect4 = RESET_STATE;
        linecounter4 = RESET_STATE;
        detect5 = RESET_STATE;
        linecounter5 = RESET_STATE;
        detect6 = RESET_STATE;
        linecounter6 = RESET_STATE;
        detect7 = RESET_STATE;
        linecounter7 = RESET_STATE;
        blackline = RESET_STATE;
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
        
      default:
        break;
        
      }
      
    }
    
    if(CMD_IOT[tempc] == '^'){
      rdready = INITIAL;
      //tempc++;
    }
    
    tempc++;
    
  }
}

void Send_IOT(void){
  if(!flagid){
    strcpy(display_line[0],"   ncsu   ");
    display_changed=INITIAL;
  }
}

void Parse_IP(void){
  
  index1 = pctemp;
  tempindex = RESET_STATE;
  int i;
  
  for(i = RESET_STATE; i < IPSIZE; i++){
    
    if(index1 >= LARGE_RING_SIZE){
      index1=RESET_STATE;
      cmdcheck=RESET_STATE;
      break;
    }
    
    if(IOT_2_PC[index1] == '1'){
      
      cmdcheck1 = INITIAL;
      i=RESET_STATE;
    }
    
    if(IOT_2_PC[index1] == '\r'){
      IOT_2_PC[index1] = '\0';
      IOT_2_PC[index1+1] = '\0';
      cmdcheck1 = RESET_STATE;
    }
    
    if(cmdcheck1){
      
      if(l>=SIZEDISPLAY1){
        ++z;
        ++y;
        l=RESET_STATE;
      }
      
      address[z][tempindex++] = IOT_2_PC[index1];
      display_line[y][l] = IOT_2_PC[index1];
      
      
      IOT_2_PC[index1] = '\0';
      
      l++;
      h++;
      if(h>=OVERSIZE){
        return;
      }
    }
    
    
    index1++;
    
    if(i==IPSIZEMINUSONE){
      display_changed = INITIAL;
      flagid++;
    }
  }
}




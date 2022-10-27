//------------------------------------------------------------------------------
//
//  Description: This is the init.c file where all the init function declarations
// and definitions go
//
//  Mohamed Mohamed-Ali
//  September 14 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "macros.h"
#include  "functions.h"
#include  "msp430.h"

void Init_Conditions(void);
void Init_LEDs(void);

extern char display_line[4][11];
extern char *display[4];
extern volatile unsigned char update_display;

void Init_Conditions(void){
//------------------------------------------------------------------------------

  int i;
  for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
  }
  display_line[0][10] = 0;
  display_line[1][10] = 0;
  display_line[2][10] = 0;
  display_line[3][10] = 0;

  display[0] = &display_line[0][0];
  display[1] = &display_line[1][0];
  display[2] = &display_line[2][0];
  display[3] = &display_line[3][0];
  update_display = 0;


// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}

void Init_Ports(void){
 Init_Port1();
 Init_Port2();
 Init_Port3();
 Init_Port4();
 Init_Port5();
 Init_Port6();
}

void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
ADCCTL0 = 0; // Reset
ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
ADCCTL0 |= ADCMSC; // MSC
ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
ADCCTL2 = 0; // Reset
ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
ADCCTL2 = 0; // Reset
ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
ADCCTL0 |= ADCENC; // ADC enable conversion.
ADCCTL0 |= ADCSC; // ADC start conversion.
}






//------------------------------------------------------------------------------
//
//  Description: This is the adc c file where all the software needed to make
//  the adc functional in order to detect the black line
//  Mohamed Mohamed-Ali
//  October 5 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

char adc_char [4];
volatile unsigned int ADC_Left_Detect=0;
volatile unsigned int ADC_Right_Detect=0;
unsigned int ADC_Thumb;
unsigned int ADC_Channel;
extern char display_line[4][11];
int i;
extern volatile unsigned char display_changed;
extern unsigned int checkadc;

//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
void HEXtoBCD(int hex_value){
  int value;
  for(i=0; i < QUAD; i++) {
    adc_char[i] = '0';
  }
  while (hex_value > 999){
    hex_value = hex_value - 1000;
    value = value + 1;
    adc_char[0] = 0x30 + value;
  }
  value = 0;
  while (hex_value > 99){
    hex_value = hex_value - 100;
    value = value + 1;
    adc_char[1] = 0x30 + value;
  }
  value = 0;
  while (hex_value > 9){
    hex_value = hex_value - 10;
    value = value + 1;
    adc_char[2] = 0x30 + value;
  }
  adc_char[3] = 0x30 + hex_value;
}
//-----------------------------------------------------------------

//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location){
  //-------------------------------------------------------------
  int i;
  unsigned int real_line;
  real_line = line;
  for(i=0; i < QUAD; i++) {
    display_line[real_line][i+location] = adc_char[i];
  }
  display_line[3][9] = 's';
  display_changed = INITIAL;
}
//-------------------------------------------------------------

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
  case ADCIV_NONE:
    break;
  case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
    // before its previous conversion result was read.
    break;
  case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
    break;
  case ADCIV_ADCHIIFG: // Window comparator interrupt flags
    break;
  case ADCIV_ADCLOIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCINIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
    ADCCTL0 &= ~ADCENC; // Disable ENC bit.
    switch (ADC_Channel++){
    case 0x00: // Channel A2 Interrupt
      ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
      ADC_Right_Detect = ADCMEM0; // Move result into Global
      ADC_Right_Detect = ADC_Right_Detect >> 2; // Divide the result by 4
      //HEXtoBCD(ADC_Right_Detect); // Convert result to String
      //adc_line(0,0); // Place String in Display
      break;
    case 0x01:
      ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
      ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
      ADC_Left_Detect = ADCMEM0; // Move result into Global
      ADC_Left_Detect = ADC_Left_Detect >> 2; // Divide the result by 4
      //HEXtoBCD(ADC_Left_Detect); // Convert result to String
      //adc_line(0,5); // Place String in Display
      break;
    case 0x02:
      ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
      ADCMCTL0 |= ADCINCH_2; // Enable Next channel A2
      ADC_Thumb = ADCMEM0; // Move result into Global
      ADC_Thumb = ADC_Thumb >> 2; // Divide the result by 4
      //HEXtoBCD(ADC_Thumb); // Convert result to String
      //adc_line(1,0); // Place String in Display
      break;
    case 0x03:
      ADC_Channel = 0;
      break;
      default:
        break;
    }
    ADCCTL0 |= ADCENC; // ADC enable conversion.
    ADCCTL0 |= ADCSC; // ADC start conversion.
  default:
    break;
  }
}

void ADC_Check(void){
  if(checkadc){
    Init_ADC();
    checkadc = RESET_STATE;
  }
}
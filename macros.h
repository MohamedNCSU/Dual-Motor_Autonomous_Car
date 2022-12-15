//------------------------------------------------------------------------------
//
//  Description: This is a header file with all the necessary "#define" statements
// in order to make the all code work properly
//
//  Mohamed Mohamed-Ali
//  September 14 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// STATES ======================================================================
#define NONE ('N')
#define STRAIGHT ('L')
#define CIRCLE ('C')
#define NEXTCIRCLE ('D')
#define TRAVEL ('T')
#define NEXTTRAVEL ('Q')
#define FIGURE_8 ('G')
#define TRIANGLE ('T')
#define CW ('A')
#define CCW ('B')
#define LEFT ('P')
#define WAIT ('W')
#define START ('S')
#define RUN ('R')
#define END ('K')
#define STOP ('E')
#define TURN ('P')
#define WHEEL_COUNT_TIME (100) // prev 10
#define RIGHT_COUNT_TIME (12) // prev 99
#define LEFT_COUNT_TIME (12) // prev 73
#define TRAVEL_DISTANCE (5) //PREV 6
#define WAITING2START (50)

#define PRESSED (0)
#define RELEASED (1)
#define NOT_OKAY (0)
#define OKAY (1)
#define DEBOUNCE_TIME (10)
#define DEBOUNCE_RESTART (0)

#define CIRCLE_TRAVEL_DISTANCE (16)
#define CIRCLE_WHEEL_COUNT_TIME (51)
#define CIRCLE_RIGHT_COUNT_TIME (50)
#define CIRCLE_LEFT_COUNT_TIME (15)
#define CW_TRAVEL_DISTANCE (2) // prev 5
#define CW_WHEEL_COUNT_TIME (51)
#define CW_RIGHT_COUNT_TIME (48)
#define CW_LEFT_COUNT_TIME (12)
#define CCW_TRAVEL_DISTANCE (2) // prev 6
#define CCW_RIGHT_COUNT_TIME (12)
#define CCW_LEFT_COUNT_TIME (48) // prev 49
#define CCW_WHEEL_COUNT_TIME (50)
#define LEFT_TRAVEL_DISTANCE (1) 
#define LEFT_RIGHT_COUNT_TIME (1) // PREV 1
#define LEFT_LEFT_COUNT_TIME (40) // PREV 39
#define LEFT_WHEEL_COUNT_TIME (51) // PREV 50
#define RIGHT_FORWARD ('Z')
#define RIGHT_REVERSE ('Y')
#define LEFT_FORWARD ('X')
#define LEFT_REVERSE ('V')

#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define RIGHT_REVERSE_SPEED (TB3CCR2)
#define LEFT_FORWARD_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)

#define WHEEL_PERIOD (40000) // prev 37000
#define WHEEL_ON (7500) // prev 4800
#define RIGHT_ON (6000) //prev 3400
#define LEFT_ON (6000) // prev 3430
#define WHEEL_OFF (0)
#define THREEK (4000)
#define BLACKLINE (600) // prev 250, 125
#define BLACKLINEWHEEL (300)
#define LINE_INTERVAL_CHECK (30)
#define FASTWHEEL (13200)
#define SLOWWHEEL (5900)
#define BEGINNING (0)
#define INTERCEPTWHEEL (6105)
#define TURNFAST (11000)
#define BC (6300)
#define O5 (15)
#define FIVESEC (50)
#define SEVSEC (70)
#define TK (10000)
#define CR (6800)
#define CS (5100)
#define FIVEF (54)
#define FOF (45)
#define LF (10910)
#define RF (10820)
#define THSEC (30)
#define THSEC1 (31)
#define SSEC1 (61)
#define SSEC2 (62)
#define SSEC3 (63)
#define SSEC5 (65)
#define NSEC2 (92)
#define NSEC3 (93)
#define O23 (123)
#define O24 (124)
#define O33 (133)
#define EE (88)
#define IPSIZE (21)
#define IPSIZEMINUSONE (20)
#define LARGE_RING_SIZE (128)
#define BUCOS16 (17)
#define CUCOS16 (52)
#define TWOWHEEL (2)
#define THMS (3)
#define QUAD (4)
#define FIFTHPOS (5)
#define SIZEDISPLAY (11)
#define SIZEDISPLAY1 (10)
#define OVERSIZE (12)
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //
#define TEST_PROBE           (0x01) // 3.0 TEST PROBE
#define RED_LED                (0x01) // 1.0 RED LED 0
#define GRN_LED                (0x40) // 6.6 GREEN LED

#define TB0CCR0_INTERVAL (50000)
#define TB0CCR1_INTERVAL (50000)
#define TB1CCR0_INTERVAL (50000)
#define TB1CCR1_INTERVAL (50000)
#define TB2CCR0_INTERVAL (50000)
#define TB2CCR1_INTERVAL (2500)

#define CNTR__2 (32768)
#define CNTR__10 (6553)
#define INITIAL (1)
#define FIFTYMSINTERVAL (10)

// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define A4_SEEED (0x10) // 4 A4_SEEED
#define V_THUMB (0x20) // 5 V_THUMB
#define UCAORXD (0x40) // 6 Back Channel UCA0RXD
#define UCAOTXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define RESET_LCD (0x01) // 0 RESET LCD
#define Check_Bat (0x02) // 1 Check ADC Voltages
#define IR_LED (0x04) // 2 IR_LED
#define SW2 (0x08) // 3 SW2
#define IOT_RUN_CPU (0x10) // 4 IOT_RUN_CPU
#define DAC_ENB (0x20) // 5 DAC_ENB
#define LFXOUT (0x40) // 6 XOUTR
#define LFXIN (0x80) // 7 XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define OA2O (0x02) // 1 OA2O
#define OA2N (0x04) // 2 OA2N
#define OA2P (0x08) // 3 OA2P
#define SMCLK (0x10) // 4 SMCLK
#define DAC_CNTL (0x20) // 5 DAC signal from Processor
#define IOT_LINK_CPU (0x40) // 6 IOT_LINK_CPU
#define IOT_EN_CPU (0x80) // 7 IOT_EN_CPU

// Port 4 Pins
#define DAC_CNTL1 (0x01) // 0 DAC_CNTR1
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

//Port 5 Pins
#define V_BAT (0x01)
#define V_5_0 (0x02)
#define V_DAC (0x04)
#define V_3_3 (0x08)
#define IOT_BOOT_CPU (0x10)

//Port 6 Pins
#define R_FORWARD (0x01)
#define R_REVERSE (0x02)
#define L_FORWARD (0x04)
#define L_REVERSE (0x08)
#define LCD_BACKLITE (0x10)
#define P6_5 (0x20)
#define GRN_LED (0x40)


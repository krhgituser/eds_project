//------------------------------------------------------------------------------------------------
// LCD16x2.h
//
// Date : 9April2017
//
// Description: header for API and device driver code for the 16x2 LCD daughter board
//-------------------------------------------------------------------------------------------------
#ifndef LCD16x2_H
#define LCD16x2_H

#include "hydronic_types.h"

#define LCD_ROW             2   // 2 Line
#define LCD_COL             16  // 16 Char per line
#define LCD_BUS             4   // Interface 4 Bit mode
#define LCD_UPDATE_PERIOD   300000 // .3s display refresh interval (300000000us)
 
#define PORT_LCD_RS     7   // GPIOY.BIT3(#83)
#define PORT_LCD_E      0   // GPIOY.BIT8(#88)
#define PORT_LCD_D4     2   // GPIOX.BIT19(#116)
#define PORT_LCD_D5     3   // GPIOX.BIT18(#115)
#define PORT_LCD_D6     1   // GPIOY.BIT7(#87)
#define PORT_LCD_D7     4   // GPIOX.BIT7(#104)

#define PI_GPIOX8      14   // wiringPi port 14 = GPIOX.8
#define PI_GPIOX9      13   // wiringPi port 13 = GPIOX.9
#define PI_GPIOX10     12   // wiringPi port 12 = GPIOX.10
#define PI_GPIOX20     10   // wiringPi port 10 = GPIOX.20

//------------------------------------------------------------------------------------------------------------
// Buttons defined for 16x2 LCD Daughter Board:
//------------------------------------------------------------------------------------------------------------
#define PORT_BUTTON1    5
#define PORT_BUTTON2    6
 
extern const int ledPorts[];
#define MAX_LED_CNT sizeof(ledPorts) / sizeof(ledPorts[0])


// function prototypes
void LcdUpdate(char *);
void LedButtonUpdate();
s32 lcdBoardInit();


#endif

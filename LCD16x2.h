//------------------------------------------------------------------------------------------------
// LCD16x2.h
//
// Date : 14March2017
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

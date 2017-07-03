// user_interface.cpp
//
// Implements the user interface class type and member methods.
// This is physically distinct from the standard I/O interface
// that is only operational during debugging activity.
//
// The user interface is composed of the following three subsystems:
//    - 16x2 LCD  (for user message display)
//    - 7 discrete LEDs  (for machine state & status indication)
//    - 2 push button switches  (to support user control input)
//--------------------------------------------------------------

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <wiringPi.h>
#include <lcd.h>
#include "UI_class.h"


class UI_class
{  // User Interface Class
   // encapsulates user input/output interaction with the Daughter Board
   
public:
      UI_class();    // constructor
   
   
   private:
      unsigned char lcdFb[LCD_ROW][LCD_COL] = {0, };
      int lcdHandle  = 0;

      const int ledPorts[] =
      {  //-------------------------------------------------------------------
         // LED wiringPI port assignments defined for 16x2 LCD Daughter Board
         //-------------------------------------------------------------------
          21, 
          22,
          23,
          24,
          11,
          26,
          27,
      };
   
   
};


//------------------------------------------------------------------------------------
// UI_class    class constructor method
//
// Initializes user interface device driver to communicate with the 16X2 LCD display board 
// Includes initialization of LED and pushbutton ports included on the board
//
// parameters
//    input:  none
//    output: initialization status (0 = success; -1 or other = failure)
//------------------------------------------------------------------------------------
UI_class initializeUI()
{
   lcdHandle = lcdInit(LCD_ROW, LCD_COL, LCD_BUS, PORT_LCD_RS, PORT_LCD_E,
               PORT_LCD_D4, PORT_LCD_D5, PORT_LCD_D6, PORT_LCD_D7, 0, 0, 0, 0);
 
   if(lcdHandle < 0)
   {
      return -1;
   }

   // GPIO Init(LED Port all as outputs)
   for(unsigned int i = 0; i < MAX_LED_CNT; i++)
   {
      pinMode(ledPorts[i], OUTPUT);
      pullUpDnControl(ledPorts[i], PUD_OFF);
   }

   for(unsigned int i = 0; i < MAX_LED_CNT; i++)
   {
      digitalWrite (ledPorts[i], 0);      // clear all LEDs      
   }
  
   // Button Pull Up Enable.
   pinMode(PORT_BUTTON1, INPUT);
   pullUpDnControl(PORT_BUTTON1, PUD_UP);
   pinMode(PORT_BUTTON2, INPUT);
   pullUpDnControl(PORT_BUTTON2, PUD_UP);

   // GPIO Init(control signals all as outputs) TODO: move these to mixing valve class
   pinMode(PI_GPIOX8, OUTPUT);
   pullUpDnControl(PI_GPIOX8, PUD_OFF);
   pinMode(PI_GPIOX9, OUTPUT);
   pullUpDnControl(PI_GPIOX9, PUD_OFF);
   pinMode(PI_GPIOX10, OUTPUT);
   pullUpDnControl(PI_GPIOX10, PUD_OFF);
   pinMode(PI_GPIOX20, OUTPUT);
   pullUpDnControl(PI_GPIOX20, PUD_OFF);

   return 0;
}





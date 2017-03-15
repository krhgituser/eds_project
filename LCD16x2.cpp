//------------------------------------------------------------------------------------------------
// LCD16x2.cpp
//
// Date : 14March2017
//
// Description: API and device driver code for the 16x2 LCD daughter board for Odroid-C2
//-------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <ctime>
#include <string.h>
#include <wiringPi.h>
#include <lcd.h>

#include "LCD16x2.h"
#include "hydronic_types.h"


static unsigned char lcdFb[LCD_ROW][LCD_COL] = {0, };
static int lcdHandle  = 0;


//------------------------------------------------------------------------------------------------------------
// LED port pin assignments defined for 16x2 LCD Daughter Board:
//------------------------------------------------------------------------------------------------------------
const int ledPorts[] = {
    21, 
    22,
    23,
    24,
    11,
    26,
    27,
};

static unsigned short display_mode = 0;   // display mode flag for 16x2 character display


//------------------------------------------------------------------------------------
// lcdBoardInit
//
// Initializes interface device driver to communicate with the 16X2 LCD display board 
// Includes initialization of LED and pushbutton ports included on the board
//
// parameters
//    input:  none
//    output: initialization status (0 = success; -1 or other = failure)
//------------------------------------------------------------------------------------
s32 lcdBoardInit()
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
      pullUpDnControl(PORT_BUTTON1, PUD_OFF);
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

   return 0;
}


//------------------------------------------------------------------------------------
// LcdUpdate
//
// updates 16x2 LCD Daughter Board display with time and eventually other info...
//
// parameters
//    input:  reg_string   pointer to register array string containing AS5601 register value
//    output: none
//------------------------------------------------------------------------------------
void LcdUpdate(char *reg_string)
{
   int i, j;
 
   memset((void *)&lcdFb, ' ', sizeof(lcdFb));
 
   if (display_mode)
   {  // mode 1... display date & time
      time_t t;
      time(&t);   // fetch current time
      sprintf((char *)lcdFb[0], "Time %s", ctime(&t));  // inject formatted date/time string  
      lcdFb[0][strlen((char *)lcdFb[0])-1] = ' ';  // remove unwanted newline planted by ctime()
   }
   else
   {  // mode 0... display string passed as parameter (presumably created by register read operation)
      strcpy((char *)lcdFb[0], reg_string);
   }   
   lcdFb[0][strlen((char *)lcdFb[0])] = ' '; // replace string terminator null 
 
   for(i = 0; i < LCD_ROW; i++)
   {
      lcdPosition(lcdHandle, 0, i);
      for(j = 0; j < LCD_COL; j++)
         lcdPutchar(lcdHandle, lcdFb[i][j]); // send each character to the LCD display
   }
}


//------------------------------------------------------------------------------------
// LedButtonUpdate
//
// board LED and pushbutton data update
//
// parameters
//    input:  none
//    output: none
//------------------------------------------------------------------------------------
void LedButtonUpdate()
{
   static unsigned short ledPos = MAX_LED_CNT-1, led_state = 0, led_mode = 0;
 
   //  LED Control - just diagnostic sequence through LEDs for now 
   switch(led_mode)
   {
   default:
   case 0:  // toggle all LEDs to opposit state
      led_state = led_state ? 0 : 1;    // toggle state
      for(unsigned int i = 0; i < MAX_LED_CNT; i++)
      {  // set all LEDs to new state
         digitalWrite (ledPorts[i], led_state);     
      }
      break;
   case 1:  // sequence through LEDs ascending
      digitalWrite(ledPorts[ledPos], 0);     // clear currently lit LED
      ++ledPos;
      ledPos %= MAX_LED_CNT;                 // handle wrap of LED port list index
      digitalWrite(ledPorts[ledPos], 1);     // light next LED in sequence
      break;
   case 2:  // sequence through LEDs descending
      digitalWrite(ledPorts[ledPos], 0);     // clear currently lit LED
      if (ledPos) --ledPos;
      else ledPos = MAX_LED_CNT-1;
      digitalWrite(ledPorts[ledPos], 1);     // light next LED in sequence
      break;
   }
  
   // button status read
   if(!digitalRead(PORT_BUTTON1))
   {  // button 1 pressed...
      while(!digitalRead(PORT_BUTTON1)) ; // awaiting button release
      // button 1 released

      // advance to next LED mode
      ++led_mode;
      led_mode %= 3; // handle wrap
   };

   if(!digitalRead(PORT_BUTTON2))
   {  // button 2 pressed...
      while(!digitalRead(PORT_BUTTON2)) ; // awaiting button release
      // button 2 released
   
      display_mode = display_mode ? 0 : 1;   // toggle character display mode
   };
}



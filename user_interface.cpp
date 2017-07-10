// user_interface.cpp
//
// Date : 10July2017
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
#include "user_interface.h"


//------------------------------------------------------------------------------------
// getInstance    gets the class instance pointer
//
// parameters
//    input:  none
//    output: pointer to class instance
//------------------------------------------------------------------------------------
UI *UI::getInst()
{
   static UI instance(1);   // this gets initialized upon first access
   return &instance;
}


//------------------------------------------------------------------------------------
// UI    class constructor
//
// parameters
//    input:  dm   = display_mode initializer
//            h    = lcdHandle initializer
//            fill = LCD message array initializer
//------------------------------------------------------------------------------------
UI::UI(unsigned char dm, int h, unsigned char fill)
{
   display_mode = dm;
   lcdHandle = h;
   std::fill(lcdFb[0], lcdFb[0] + (LCD_ROW * LCD_COL), fill);
}


//------------------------------------------------------------------------------------
// initialize_API
//
// Initializes user interface API to communicate with the 16X2 LCD display board 
// Includes initialization of LED and pushbutton ports included on the board
//
// parameters
//    input:  none
//    output: initialization status (0 = success; -1 or other = failure)
//------------------------------------------------------------------------------------
int UI::initialize_API()
{
   static bool API_init = false;    // flag to indicate whether API has been initialized

   if (!API_init)
   {  // not previously initialized...
      display_mode = 0;

      std::fill(lcdFb[0], lcdFb[0] + (LCD_ROW * LCD_COL), 0);

      lcdHandle = lcdInit(LCD_ROW, LCD_COL, LCD_BUS, PORT_LCD_RS, PORT_LCD_E, PORT_LCD_D4,
                                    PORT_LCD_D5, PORT_LCD_D6, PORT_LCD_D7, 0, 0, 0, 0);
    
      std::cout << "initialize_API ";


      if(lcdHandle >= 0)
      {
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

         std::cout << "Success...";
         
         API_init = true;
      }
      else
      {
         std::cout << "Failed";
      }

      std::cout << std::endl;
      
   }
   return lcdHandle;
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
void UI::LcdUpdate(char *reg_string)
{
   int i, j;
 
   memset((void *)&lcdFb, ' ', sizeof(lcdFb));

   switch (display_mode)
   {
      default:
      case 0:  // mode 0... display string passed as parameter (presumably created by register read operation)
         strcpy((char *)lcdFb[0], reg_string);
         break;
      case 1:  // mode 1... display date & time
         time_t t;
         time(&t);   // fetch current time
         sprintf((char *)lcdFb[0], "Time %s", ctime(&t));  // inject formatted date/time string  
         lcdFb[0][strlen((char *)lcdFb[0])-1] = ' ';  // remove unwanted newline planted by ctime()
         break;
      case 2:  // mode 3... display string passed as parameter (presumably created by register read operation)
         strcpy((char *)lcdFb[0], "Relay Unit Test");
         break;
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
void UI::LedButtonUpdate()
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
      ++display_mode %= 3; // handle wrap
   };
}


//------------------------------------------------------------------------------------
// toggleGPIOSignals
//
// Unit test for exercising the relay output control signals on the interface board
//
// parameters
//    input:  none
//    output: none
//------------------------------------------------------------------------------------
void UI::toggleGPIOSignals()
{
   // Test function for 3 GPIO output signals tied to connetor P5 on the 16x2 LCD board.
   // Signals are GPIOX.9 (pin 3); GPIOX.10 (pin 4); GPIOX.8 (pin 5).
   // These will be used to issue control orders for Boiler Demand, Valve Open, and Valve Close.
      
   if (display_mode == 2)
   {
      static int sequence = 0;
      static bool stateGPIOX9=false, stateGPIOX10=false, stateGPIOX8=false;
      switch(sequence)
      {
         default:
         case 0:
            digitalWrite (PI_GPIOX9, stateGPIOX9);
            stateGPIOX9 = !stateGPIOX9;
            break;
         case 1:
            digitalWrite (PI_GPIOX10, stateGPIOX10);
            stateGPIOX10 = !stateGPIOX10;
            break;
         case 2:
            digitalWrite (PI_GPIOX8, stateGPIOX8);
            stateGPIOX8 = !stateGPIOX8;
            break;
      }
      ++sequence;
      sequence %= 3;
   }
}

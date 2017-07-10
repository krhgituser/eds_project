// user_interface.h
//
// Date : 10July2017
//
// Description: header for user interface API for the 16x2 LCD daughter board API code
//-------------------------------------------------------------------------------------------------
#ifndef UI_H
#define UI_H

//-------------------------------------------------------------------------------------------------
// API definitions for the 16x2 LCD daughter board API code
//-------------------------------------------------------------------------------------------------
#define LCD_ROW             2   // 2 Line
#define LCD_COL             16  // 16 Char per line
#define LCD_BUS             4   // Interface 4 Bit mode
#define LCD_UPDATE_PERIOD   300000 // .3s display refresh interval (300000000us)
 
#define PORT_LCD_RS     7   // wiringPi port  7 = GPIOY.BIT3(#83)
#define PORT_LCD_E      0   // wiringPi port  0 = GPIOY.BIT8(#88)
#define PORT_LCD_D4     2   // wiringPi port  2 = GPIOX.BIT19(#116)
#define PORT_LCD_D5     3   // wiringPi port  3 = GPIOX.BIT18(#115)
#define PORT_LCD_D6     1   // wiringPi port  1 = GPIOY.BIT7(#87)
#define PORT_LCD_D7     4   // wiringPi port  4 = GPIOX.BIT7(#104)

#define PI_GPIOX8      14   // wiringPi port 14 = GPIOX.8
#define PI_GPIOX9      13   // wiringPi port 13 = GPIOX.9
#define PI_GPIOX10     12   // wiringPi port 12 = GPIOX.10
#define PI_GPIOX20     10   // wiringPi port 10 = GPIOX.20

//------------------------------------------------------------------------------------------------------------
#define PORT_BUTTON1    5  // Buttons defined for 16x2 LCD Daughter Board:
#define PORT_BUTTON2    6
 
#define MAX_LED_CNT     7  // number of LED ports supported on the board
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


#define ui (UI::getInst())   // client user shorthand name alias for user interface singleton class pointer

class UI
{  // User Interface Class (Singleton pattern ensures only one instance)
   // encapsulates user input/output interaction with the Daughter Board
   // By using a private static pointer and a public static accessor method, the class is responsible for its
   // own global pointer and "initialization on first use". The client uses only the public accessor method.

   public:

      static UI *getInst();  // no-heap accessor method to generate (once) and return the class instance struct pointer

      // external user interface input & output methods go here

      int initialize_API();        // initializes user interface API
      
      void LcdUpdate(char *reg_string);   // updates 16x2 LCD Daughter Board display with time and eventually other info...

      void LedButtonUpdate();             // board LED and pushbutton data update

      void toggleGPIOSignals();           // unit test for GPIO output control signals

   
   private:
      
      UI(unsigned char dm = 0, int h = 0, unsigned char fill = 0); // constructor
   
      unsigned char lcdFb[LCD_ROW][LCD_COL]; // 16x2 LCD display device driver message array
      
      int lcdHandle;
      
      unsigned char display_mode;     // display output mode flag for 16x2 character display

      const int ledPorts[MAX_LED_CNT] =
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


#endif   // UI_H

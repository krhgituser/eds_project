//------------------------------------------------------------------------------------------------
// hydronic_startup.cpp
//
// Date : 9April2017
//
// Hydronic System Control Software Start Point
//
// Evolved from reference software for ODROID-C printing time Application.
//
// Defined port number is wiringPi port number.
//
//-------------------------------------------------------------------------------------------------
 
#include <iostream>

#include <stdio.h>      // sprintf()
 
#include <unistd.h>     // usleep()

#include "hydronic_types.h"
#include "AS5601_i2c.h"
#include "LCD16x2.h"



// function prototypes
static int SystemInit();
void toggleGPIOSignals();
int main();

 
//------------------------------------------------------------------------------------
// useful debug tool
//   std::cout << __func__ << ": __func__ = current function name" << std::endl;
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// SystemInit
//
// Daughter Board 16x2 LCD, LED and push button Initialization
// also I2C interface Initialization for AS5601 rotary position sensor used for mixing valve position monitoring
//
// parameters
//    input:  none
//    output: status (0 = success;  -1 = failure)
//------------------------------------------------------------------------------------
static int SystemInit()
{
   // initialization for 16X2 LCD display daughter board
   if(lcdBoardInit() < 0)
   {
      std::cout << __func__ << ": lcd Init failed" << std::endl;
      return -1;
   }

   // I2C initialization for AS5601 rotary position sensor for mixing valve position monitoring
   if (as5601I2cInit() < 0)
   {
      std::cout << __func__ << ": AS5601 I2C Init failed" << std::endl;
      return -1;
   }

   return  0;
}
 

//------------------------------------------------------------------------------------
// main
//
// Hydronic heating controller application - initial startup function
//
// parameters
//    input:  none
//    output: status (0 = success;  -1 = failure)
//------------------------------------------------------------------------------------
int main()
{
   std::cout << "Starting Hydronic System Control Software..." << std::endl;

   if (wiringPiSetup() != 0)
   {      
      std::cout << __func__ << ": wiringPi Init failed" << std::endl;
      return -1;
   }
 
   if (SystemInit() < 0)
   {
      std::cout << __func__ << ": System Init failed" << std::endl;
      return -1;
   }


   std::cout << __func__ << ": System Init Success!" << std::endl;
   std::cout << __func__ << ": Launching primary application control loop..." << std::endl;

   // loop forever running hydronic controller application
   while(true)
   {
      char as5601_regstring[32];

      usleep(LCD_UPDATE_PERIOD); // loop delay

   // STUB STUB STUB
   // this will evolve as development progresses...

      if (as5601_get_angle() < 0)
      {
         std::cout << __func__ << ": AS5601_status register read failed" << std::endl;
         sprintf(as5601_regstring, "-Angle register-  read error");  
      }
      else
      {
         unsigned long degrees = (as5601.angle * 45) / 512; // convert to degrees
         sprintf(as5601_regstring, "-Angle register- degrees = %d", (int)degrees);  
      }

      LedButtonUpdate();   // refresh LEDs & read pushbuttons
                           // (TODO: pushbutton detect should be re-designed for interrupt detect or at least handled in separate thread)

      LcdUpdate(as5601_regstring);   // refresh LCD screen content

      toggleGPIOSignals(); // test GPIO output port signals
   }
 
   return 0 ;
}

void toggleGPIOSignals()
{
   // test function for 3 GPIO output signals tied to connetor P5 on 16x2 LCD board
   // signals are GPIOX.9 (pin 3); GPIOX.10 (pin 4); GPIOX.8 (pin 5)
   // these will be used to issue control orders for Boiler Demand, Valve Open, and Valve Close
   
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

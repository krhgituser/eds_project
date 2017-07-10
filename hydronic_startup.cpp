//------------------------------------------------------------------------------------------------
// hydronic_startup.cpp
//
// Date : 10uly2017
//
// Hydronic System Control Software Start Point
//
// Evolved from weather board reference software for ODROID-C.
//
//-------------------------------------------------------------------------------------------------
 
#include <iostream>

#include <stdio.h>      // sprintf() 
#include <unistd.h>     // usleep()

#include "hydronic_types.h"
#include "AS5601_i2c.h"
#include "user_interface.h"


// function prototypes
static int SystemInit();
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
//   if (UI::getInst()->initialize_API() < 0)  // run user interface initializer
   if (ui->initialize_API() < 0)  // run user interface initializer
   {
      std::cout << __func__ << ": UI Init failed" << std::endl;
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
// Hydronic heating controller application (such as it is)
//
// parameters
//    input:  none
//    output: status (0 = success;  -1 = failure)
//------------------------------------------------------------------------------------
int main()
{
   std::cout << "Starting Hydronic System Control Software..." << std::endl;

   if (wiringPiSetup() != 0)  // install/activate Odroid GPIO device driver
   {      
      std::cout << __func__ << ": wiringPi Init failed" << std::endl;
      return -1;
   }
 
   if (SystemInit() < 0)      // run application initializer
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

      ui->LedButtonUpdate();              // refresh LEDs & read pushbuttons
                                          // (TODO: pushbutton detect should be re-designed for interrupt detect or at least handled in separate thread)

      ui->LcdUpdate(as5601_regstring);    // refresh LCD screen content

      ui->toggleGPIOSignals();            // test GPIO output port signals
   }
 
   return 0 ;
}


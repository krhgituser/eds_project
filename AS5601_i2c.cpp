//------------------------------------------------------------------------------------------------
// AS5601_i2c.cpp
//
// Date : 14March2017
//
// Description: API and device driver code for AS5601 sensor
//-------------------------------------------------------------------------------------------------
#include <iostream>
//#include <cmath>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "AS5601_i2c.h"
#include "hydronic_types.h"

static int as5601Fd;     // "file" descriptor for I2C device driver transactions with AS5601 sensor
as5601_t as5601;  // AS5601 sensor driver register values structure


//------------------------------------------------------------------------------------
// as5601I2cInit
//
// Initializes Linux interface device driver to communicate with the AS5601 
// hall effect shaft position sensor wired to I2C port 2 on the Odroid-C2 board
//
// parameters
//    input:  none
//    output: port open status (0 = success; -1 or other = failure)
//------------------------------------------------------------------------------------
s32 as5601I2cInit()
{
   int status = 0;
   s32 com_rslt = 0;

   as5601Fd = open(I2C_MASTER_DEVICE_STRING, O_RDWR);
   if (as5601Fd < 0)
   {
      std::cout << __func__ << ": AS5601 I2C port open failed" << std::endl;
      return -1;
   }
   status = ioctl(as5601Fd, I2C_SLAVE, AS5601_I2C_ADDRESS);
   if (status < 0)
   {
      std::cout << __func__ << ": AS5601 ioctl error" << std::endl;
      status = close(as5601Fd);
      return -1;
   }

   // if needed, setup control elements in the sensor driver structure

   // stub stub stub


   usleep(100000);

   return com_rslt;
}


//------------------------------------------------------------------------------------
// as5601_I2C_bus_write
//
// Writes successive bytes to the AS5601 I2C device.  
//
// parameters
//    input:  start_addr      starting register address to write in I2C device
//            return_data     pointer to container with bytes to be written (must be large enough to contain cnt bytes)
//            cnt             number of successive bytes to write
//    output: returned val    register write status   (AS5601_ERROR if error;  otherwise something else)
//            I2C device      designated I2C register(s) now contain bytes written (assuming no errors)
//------------------------------------------------------------------------------------
signed char as5601_I2C_bus_write(unsigned char start_addr, unsigned char *data_out, unsigned char cnt)
{
   signed char iError = AS5601_SUCCESS;

   if (write(as5601Fd, &start_addr, 1) < 0)        // send starting register address to slave
      iError = AS5601_ERROR;

   if (write(as5601Fd, data_out, cnt) < 0)   // send starting register address to slave
      iError = AS5601_ERROR;

   return iError;
}


//------------------------------------------------------------------------------------
// as5601_I2C_bus_read
//
// Reads successive bytes from the AS5601 I2C device.  
//
// parameters
//    input:  start_addr      starting register address to read in I2C device
//            return_data     pointer to result container (must be large enough to contain cnt bytes)
//            cnt             number of successive bytes to read
//    output: returned val    register read status   (AS5601_ERROR if error;  otherwise something else)
//            *return_data    result container loaded with bytes read (assuming no errors)
//------------------------------------------------------------------------------------
signed char as5601_I2C_bus_read(unsigned char start_addr, unsigned char *return_data, unsigned char cnt)
{
   signed char iError = AS5601_SUCCESS;
   unsigned char byteVal;

   if (write(as5601Fd, &start_addr, 1) < 0)   // send starting register address to slave
      iError = AS5601_ERROR;

   for (unsigned char byteNum = 0; byteNum < cnt; byteNum++)
   {  // read each successive byte and accumulate result into result container
      if (read(as5601Fd, &byteVal, 1) < 0)
         iError = AS5601_ERROR;
      else
         *(return_data + byteNum) = byteVal;
   }
   return iError;
}


//------------------------------------------------------------------------------------
// as5601_get_status
//
// Reads the AS5601 I2C interface Status register value.  
//
// parameters
//    input:  none
//    output: returned val    register read status   (AS5601_ERROR if error;  otherwise something else)
//            as5601.status   struct element for Status register returns with the value read
//------------------------------------------------------------------------------------
signed char as5601_get_status()
{
	signed char com_rslt = AS5601_ERROR;
	unsigned char v_data_u8 = 0xFF;

	// read AS5601 Status register via I2C interface
	com_rslt = as5601_I2C_bus_read(AS5601_STATUS_REG, &v_data_u8, AS5601_STATUS_REG_LEN);
	as5601.status = v_data_u8;  // store result in registers struct

	return com_rslt;
}


//------------------------------------------------------------------------------------
// as5601_get_angle
//
// Reads the AS5601 I2C interface Status register value.  
//
// parameters
//    input:  none
//    output: returned val    register read status   (AS5601_ERROR if error;  otherwise something else)
//            as5601.angle    struct element for Angle register returns with the value read
//------------------------------------------------------------------------------------
signed char as5601_get_angle()
{
   signed char com_rslt = AS5601_ERROR;
   unsigned char result[2] = {0xFF, 0xFF};

   // read AS5601 Angle register via I2C interface
   com_rslt = as5601_I2C_bus_read(AS5601_ANGLE_REG, result, AS5601_ANGLE_REG_LEN);
   as5601.angle = ((result[0] << 8) & 0x0FFF) | result[1];  // store result in registers struct

   return com_rslt;
}



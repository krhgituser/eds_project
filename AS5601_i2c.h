//--------------------------------------------------------------------------
// File : AS5601.h
//
// Date : 14March2017
//
// Description: driver header for AS5601 sensor
//--------------------------------------------------------------------------
#ifndef AS5601_I2C_H
#define AS5601_I2C_H

#include <wiringPi.h>
#include "hydronic_types.h"

// function prototypes
s32 as5601I2cInit();
signed char as5601_get_status();
signed char as5601_get_angle();

signed char as5601_I2C_bus_write(unsigned char start_addr, unsigned char *data_out, unsigned char cnt);
signed char as5601_I2C_bus_read(unsigned char start_addr, unsigned char *return_data, unsigned char cnt);

// AS5601 sensor register structure (config, status & output registers)
typedef struct
{
   unsigned char zmco;        // 
   unsigned char zpos_h;      //
   unsigned char zpos_l;      //
   unsigned char conf_h;      //
   unsigned char conf_l;      //
   unsigned char abn;         //
   unsigned char pushthr;     //

   unsigned short raw_angle;  //
   unsigned short angle;      //

   unsigned char status;      //
   unsigned char agc;         //
   unsigned char magnitude_h; //
   unsigned char magnitude_l; //
} as5601_t;

extern as5601_t as5601;  // AS5601 sensor driver register values structure

//--------------------------------------------------------------------------
// ERROR CODE DEFINITIONS
#define AS5601_SUCCESS        ((signed char)0)
#define AS5601_NULL_PTR       ((signed char)-127)
#define AS5601_COMM_RES       ((signed char)-1)
#define AS5601_OUT_OF_RANGE   ((signed char)-2)
#define AS5601_ERROR          ((signed char)-1)
//--------------------------------------------------------------------------

// I2C master device interface #2 is connected to AS5601 mixing valve shaft position sensor
#define I2C_MASTER_DEVICE_STRING ("/dev/i2c-2")    // Odroid-C2 board J2 pins 27 & 28 (I2CB export gpio #207 & 208)

// 7 bit I2C slave device address (0x36) bits 1-7
#define AS5601_I2C_ADDRESS 0x36

//------------------------------------------
// AS5601 I2C REGISTER ADDRESS DEFINITIONS
// (multi-byte reg bit order is big-endian)
//------------------------------------------
#define AS5601_ZMCO_REG          (0x00)  /* ZMCO(1:0) [1byte] (read) */
#define AS5601_ZPOS_REG          (0x01)  /* ZPOS(11:0) [2byte] (read write) */
#define AS5601_CONF_REG          (0x07)  /* CONF(WD(13) FTH(12:10) SF(9:8) hyst(3:2) PM(1:0)) [2byte] (read write) */
#define AS5601_PUSHTHR_REG       (0x08)  /* PUSHTHR(7:0) [1byte] (read write) */
#define AS5601_ABN_REG           (0x09)  /* ABN(3:0) [1byte] (read write) */
#define AS5601_STATUS_REG        (0x0B)  /* STATUS(MD(5) ML(4) MH(3)) [1byte] (read) */
#define AS5601_RAW_ANGLE_REG     (0x0C)  /* RAW ANGLE(11:0) [2byte] (read) */
#define AS5601_ANGLE_REG         (0x0E)  /* ANGLE(11:0) [2byte] (read) */
#define AS5601_AGC_REG           (0x1A)  /* AGC(7:0) [1byte] (read) */
#define AS5601_MAGNATUDE_REG     (0x1B)  /* MAGNATUDE(11:0) [2byte] (read) */
#define AS5601_BURN_REG          (0xFF)  /* BURN(7:0) [1byte] Angle=0x80 Setting=0x40 (write) */

#define AS5601_ZMCO_REG_LEN      (1)
#define AS5601_ZPOS_REG_LEN      (2)
#define AS5601_CONF_REG_LEN      (2)
#define AS5601_ABN_REG_LEN       (1)
#define AS5601_PUSHTHR_REG_LEN   (1)
#define AS5601_STATUS_REG_LEN    (1)
#define AS5601_RAW_ANGLE_REG_LEN (2)
#define AS5601_ANGLE_REG_LEN     (2)
#define AS5601_AGC_REG_LEN       (1)
#define AS5601_MAGNATUDE_REG_LEN (2)
#define AS5601_BURN_REG_LEN      (1)


#endif   // AS5601_I2C_H

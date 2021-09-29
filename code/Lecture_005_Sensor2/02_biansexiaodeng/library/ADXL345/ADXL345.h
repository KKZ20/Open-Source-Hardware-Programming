#include <Wire.h>
#include <Arduino.h>

//#define DEVICE (0x53)      //ADXL345 device address
//#define TO_READ (6)        //num of bytes we are going to read each time (two bytes for each axis)

//byte buff[TO_READ] ;        //6 bytes buffer for saving data read from the device
//char str[512];              //string buffer to transform data before sending it to the serial port
//int regAddress;      //first axis-acceleration-data register on the ADXL345
extern int X_out, Y_out, Z_out;                        //three axis acceleration data
//double roll, pitch;       //Roll & Pitch are the angles which rotate by the axis X and y
//in the sequence of R(x-y-z),more info visit
// https://www.dfrobot.com/wiki/index.php?title=How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing#Introduction
//---------------- Functions
//Writes val to address register on device
void ADXL345_init(void);
void ADXL345_update(void);
void writeTo(int device, byte address, byte val);
//reads num bytes starting from address register on device in to buff array
void readFrom(int device, byte address, int num, byte buff[]);
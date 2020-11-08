/*
  VEML7700_basic.ino

  2019-09-18,  John rob
  2020-10-15,  Ryan Hopkins
  
  
  The code that was used to interface with the VEML7700 was developed by John rob, it was created 
  and posted on the internet with no required license. The program allows for easy connection to 
  the sensor without having to deal with the data sheet and figuring out the I squared C conneciton.
  
  This code was developed and funtions quite well, but it is by no means the fastest option for completing
  this project. It has quite a large bit of extra robust processing that could be removed to increase the
  preformance of the device. 
*/

#include <Wire.h>
#include "VEMLConfig.h"    //defines cmd00, aka configuration command


// -------------------------------------------------

#define Lux_Address 0x10

// --- function prototypes -------------------------
// -------------------------------------------------
void LuxSendData(uint8_t command, uint32_t data);
void LuxReceiveData(uint8_t command, uint32_t& data);


// --- Global Variables-----------------------------
// -------------------------------------------------
uint32_t data;
uint16_t command;
int VoltageInputPin = A0;
float Voltage = 0.00;
int counter = 0;
unsigned long delayStart = 0; // the time the delay started

// --- Initialization ------------------------------
// -------------------------------------------------
bool delayRunning = false; // true if still waiting for delay to finish
void setup()
{
  pinMode(VoltageInputPin, INPUT);
  Serial.begin(230400);
  //Serial.begin(115200);
  Wire.begin();
  Wire.setClock(100000);
  LuxSendData(0x00, cmd00);
  delayRunning = true; // not finished yet
  delayStart = millis();   // start delay
}


// --- Main ----------------------------------------
// -------------------------------------------------
void loop()
{
  if (delayRunning && ((millis() - delayStart) == 4000)) {
    delayRunning = false; // // prevent this code being run more then once
    Serial.println(counter);
    delay(5000);
  }
  float Voltage = float(analogRead(VoltageInputPin)) / 473 * 12 ;
 
  if (Voltage != 0.00) {
    Serial.print(String(Voltage));
    Serial.print(" V");
    
 // }
//  LuxReceiveData(0x04, data);
 // Serial.print("   ALS (Lux)  ");
 // Serial.print(data * Lux_Factor, 0);

  LuxReceiveData(0x05, data);
  Serial.print("   White (Lux)  ");
  
  Serial.println(data * Lux_Factor, 0);
  counter++;
  }
  //delay(2000);    // should be a non-blocking timer, but except this
  // code is likely to be incorporated into a larger program

}

// -------------------------------------------------
// --- functions -----------------------------------
// -------------------------------------------------

//--- send data:  ----------------------------------
void LuxSendData(uint8_t command, uint32_t data)
{
  Wire.beginTransmission(Lux_Address);
  Wire.write(command);
  Wire.write(uint8_t(data & 0xff));
  Wire.write(uint8_t(data >> 8));
  Wire.endTransmission();
}


//--- receive data  --------------------------------
void LuxReceiveData(uint8_t command, uint32_t& data)
{
  Wire.beginTransmission(Lux_Address);
  Wire.write(command);
  Wire.endTransmission(false);      // need to investigate the (false) req'ment
  Wire.requestFrom(uint8_t(Lux_Address), uint8_t(2));
  data = Wire.read();
  data |= uint32_t(Wire.read()) << 8;
}

// --- end of program ------------------------------

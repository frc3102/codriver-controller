#include <Arduino.h>
#include <Joystick.h>
#include <Wire.h>
#include <elapsedMillis.h>
// #include "i2cutil/i2cutil.h"
#include "io3102/io3102.h"

#define NUM_SWITCHES 5

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   NUM_SWITCHES, 0,      // Button Count, Hat Switch Count
                   false, false, false,  // X and Y, but no Z Axis
                   false, false, false,  // No Rx, Ry, or Rz
                   false, true,          // No rudder, but throttle
                   false, false, false); // No accelerator, brake, or steering

#define AD7995_ADDR 0x29
#define NCA9555_ADDR 0x20

Io3102 IO = Io3102(NCA9555_ADDR, AD7995_ADDR, AD7995_CONFIG | AD7995_CH0);

elapsedMillis sinceLastPoll;
#define TARGET_MILLIS 8

void setup()
{
  Wire.begin();
  IO.begin();
  // Serial.begin(9600);
  Joystick.setThrottleRange(0, 1024);
  Joystick.begin(false);
}

void loop()
{
  if (sinceLastPoll > TARGET_MILLIS)
  {
    Adc7995Report adc = IO.ReadADC();
    DioReport dio = IO.ReadDIO();
    Joystick.setThrottle(adc.CH0);
    for (int i = 0; i < NUM_SWITCHES; i++)
    {
      Joystick.setButton(i, dio.isPressed(i));
    }
    Joystick.sendState();
    sinceLastPoll = 0;
  }
}
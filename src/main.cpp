#include <Arduino.h>
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   1, 0,                 // Button Count, Hat Switch Count
                   false, false, false,  // X and Y, but no Z Axis
                   false, false, false,  // No Rx, Ry, or Rz
                   false, true,          // No rudder, but throttle
                   false, false, false); // No accelerator, brake, or steering

#define BUTTON0 9
#define THROTTLE 10

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON0, INPUT_PULLUP);
  pinMode(THROTTLE, INPUT);
  Joystick.setThrottleRange(0, 1024);
  Joystick.begin();
}

int lastButtonState = 0;
int throttleState = 0;

void loop()
{
  int currentButtonState = !digitalRead(BUTTON0);
  if (currentButtonState != lastButtonState)
  {
    Joystick.setButton(0, currentButtonState);
    lastButtonState = currentButtonState;
  }
  throttleState = analogRead(THROTTLE);
  Joystick.setThrottle(throttleState);
  delay(50);
}
//==============================================================================
#include "config.h"

#include <Servo.h>


//==============================================================================
Servo theServo;

//==============================================================================
bool MovementDetected(void)
{
  for(int cnt = 0; cnt < 10; cnt++)
  {
    if(digitalRead(pinMovementSensor) != MovementDetectionLevel)
    {
      return false;
    }
  }
  return true;
}

//==============================================================================
void blinkEyes()
{
  for(int cnt = 0; cnt < 10; cnt++)
  {
    analogWrite(pinEyes, (cnt & 0x01)? 255 : 0);
    delay(100);
  }  
}

//==============================================================================
void setup()
{
  theServo.attach(pinServo);
  theServo.write(IdlePosition);

  pinMode(pinMovementSensor, INPUT);

  // WARNING: To use PWM ("analog" output) you dont have to configure pin
  analogWrite(pinEyes, 0);
}

//==============================================================================
void loop()
{
  if(MovementDetected())
  {
    analogWrite(pinEyes, 255);

    for(int cnt = 0; cnt < 5; cnt++)
    {
      theServo.write(Shake_2_Position);
      blinkEyes();

      theServo.write(Shake_1_Position);
      blinkEyes();
    }

    analogWrite(pinEyes, 255);

    for(int pos = Shake_1_Position; pos >= IdlePosition; pos--)
    {
      theServo.write(pos);
      analogWrite(pinEyes, map(pos, Shake_1_Position, IdlePosition, 255, 0));
      delay(map(pos, Shake_1_Position, IdlePosition, 100, 1));
    }

    analogWrite(pinEyes, 0);
    delay(1000);
  }
}

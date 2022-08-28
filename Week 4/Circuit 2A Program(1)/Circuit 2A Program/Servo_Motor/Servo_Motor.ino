/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myServo;  // create servo object to control a servo

int val;    // variable for servo position

void setup()
{
  myServo.attach(4);  // attaches the servo on pin 4 to the servo object
}

void loop()
{
  for (val = 45; val <= 135; val++)
  {
    myServo.write(val);                  // sets the servo position
    delay(15);                           // waits for the servo to get there
  }
    for (val = 135; val >= 45; val--)
  {
    myServo.write(val);                  // sets the servo position
    delay(15);                           // waits for the servo to get there */
  }
}

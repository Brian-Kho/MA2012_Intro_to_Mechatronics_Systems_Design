int potentPin = A0;
int togglePin = 9;
int pushPin = 7;
int servoPin = 4;
int dcPinB = 3;  //analog pin
int dcPinA = 2;
int degree = 0;
int potent = 0;
int pushState = 0;

#include <Servo.h>

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(potentPin, INPUT);
  pinMode(togglePin, INPUT);
  pinMode(pushPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(dcPinA, OUTPUT);
  pinMode(dcPinB, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
}

int pin = 0;
void loop() {
  // put your main code here, to run repeatedly:
  potent = analogRead(potentPin);
  degree = round(potent/11.4);
  Serial.println(degree);
  myServo.write(degree);
  delay(15);
  if(degree >= 40 || degree <= 60){
    pushState = digitalRead(pushPin);
    if(pushState == LOW){   //when the switch is closed
      analogWrite(dcPinB,200);
      digitalWrite(dcPinA,LOW);
      Serial.println(pushState);
      pin = analogRead(dcPinA);
      Serial.println(pin);
    }
    else{
      digitalWrite(dcPinB, 0);
      analogWrite(dcPinA, LOW);  
    }
  }  
  else{
    pushState = HIGH;  
  }
  
  
}

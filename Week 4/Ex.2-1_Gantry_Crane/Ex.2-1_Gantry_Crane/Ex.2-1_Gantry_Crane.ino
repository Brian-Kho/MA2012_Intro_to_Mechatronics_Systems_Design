int potentPin = A0;
int togglePin = 12;
int pushPin = 13;
int ledPin = 7;

int servoPin = 4;
int degree = 0;
int potent = 0;
int pushState = 0;
int toggleState = 0;

volatile long int encoder_pos = 0;
int motor_speed;
int encoderPinA = 2;
int encoderPinB = 3;
int dcPin1 = 9;  
int dcPin2 = 10;
int error = 0;
int setPos = 0;
char incomingByte;

#include <Servo.h>

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(potentPin, INPUT);
  pinMode(togglePin, INPUT);
  pinMode(pushPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  pinMode(servoPin, OUTPUT);
  myServo.attach(servoPin);
  
  pinMode(dcPin1, OUTPUT);
  pinMode(dcPin2, OUTPUT);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  pushState = digitalRead(pushPin);
  potent = analogRead(potentPin);
  degree = round(potent/11.4); //we want to control servo motor rotates between 0 to 90 degs, potent_max is 1023, thus divided by 11.4 is approx. 90 degs
  Serial.println(degree);
  myServo.write(degree);
  delay(15);
  if(degree >= 40 && degree <= 60){
    pushState = digitalRead(pushPin);
    toggleState = digitalRead(togglePin);
    if(toggleState == LOW){
      digitalWrite(ledPin, LOW); //turn on led to indicate forward direction 
    }
    else{
      digitalWrite(ledPin, HIGH); //turn off led to indicate backward direction
    }
    
    if(pushState == LOW && toggleState == LOW){   //when the switch is closed
      direction(1);
    }
    else if(pushState == LOW && toggleState == HIGH){
      direction(2);  
    }
    else{
      direction(0);
    }
  }
  else{
    digitalWrite(ledPin, HIGH); //turn off led to indicate backward direction
  }
}



void direction (int dir) {
  //dir 1 = forward
  //    2 = reverse
  //    0 = stop

  switch (dir){
    case (1):{
      analogWrite(dcPin1,255);
      digitalWrite(dcPin2,LOW);
      Serial.println("Forward");
      break;
    }
    case(2):{
      analogWrite(dcPin1,0);
      digitalWrite(dcPin2,HIGH);
      Serial.println("Backward");
      break;
    }
    case(0):{
      analogWrite(dcPin1,0);
      digitalWrite(dcPin2,LOW);
      Serial.println("Brake");
      break;
    }
  }
  
}

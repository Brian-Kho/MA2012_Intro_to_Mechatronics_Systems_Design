#include "pitches.h"

#include <Servo.h>
#include "UCN5804.h"

#define motorSteps 200     // change this depending on the number of steps
// per revolution of your motor

// define the pins that the motor is attached to. You can use
// any digital I/O pins.
#define dirPin   13
#define stepPin  12
#define halfPin  7
#define phasePin 6

#include <SoftwareSerial.h>
#define RxD 10
#define TxD 9

int buzzerPin = 8;
int note = NOTE_A4;

Servo myServo;  // create servo object to control a servo

int degree = 135;    // variable for servo position  
int y;

// initialize of the Stepper library:
UCN5804 myStepper(motorSteps, dirPin, stepPin, halfPin, phasePin);

char recvChar;
int on;

SoftwareSerial slave(RxD, TxD);    //Slave arduino acts as a serial communication device


//dc motor
volatile long int currentPos = 0; 
int motor_speed;
int pin1 = 5;   // motor pin1
int pin2 = 11;  // motor pin2
int encoderPinA = 2;
int encoderPinB = 3;
int error = 10; // permissible error
int targetPos = 0;   // target position, Max value is 65535, 1 rev is 371
int x1;
int x2;
int x3;
int start = 1;
int count = 0;

int pinLED1 = A4;
int pinLED2 = A5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                //start serial monitor, for communicating with the PC

  myServo.attach(4);  // attaches the servo on pin 4 to the servo object
  myStepper.setSpeed(30);

  pinMode(RxD, INPUT);                               //set mode of receive pin (from bluetooth)
  pinMode(TxD, OUTPUT);                              //set mode of transmit pin (to bluetooth)
  slave.begin(9600);                                 //start the bluetooth serial "port"

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder, RISING); // Enable the external interrupt

  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if(slave.available()){  
    count = 0;
    recvChar = slave.read();
  
//    if(recvChar=='9'){
//      digitalWrite(pinLED1, LOW);
//      digitalWrite(pinLED2, LOW);
//      digitalWrite(4, HIGH);   
//    }
//    else{
//      digitalWrite(pinLED1, HIGH);
//      digitalWrite(pinLED2, HIGH);
//    }
    
    if(recvChar=='1' || recvChar=='2'){
      Serial.print(recvChar);
      
      if(recvChar == '1'){
        digitalWrite(pinLED1, HIGH);
        delay(500);
        digitalWrite(pinLED1, LOW);
        delay(500);
        digitalWrite(pinLED1, HIGH);
        delay(500);
        digitalWrite(pinLED1, LOW);
        delay(500);
      }

      if(recvChar == '2'){
        digitalWrite(pinLED2, HIGH);
        delay(500);
        digitalWrite(pinLED2, LOW);
        delay(500);
        digitalWrite(pinLED2, HIGH);
        delay(500);
        digitalWrite(pinLED2, LOW);
        delay(500);
      }
      
      while(start == 1){
        x_manip(recvChar);
      }
      while(start == 2){
        x_manip('3');  //goes to collection window
      }
      while(start == 0){
        x_manip('0');  //goes back to origin
        if(count > 10){
          break;
        }
      }
      Serial.print("Target Postion: ");
      Serial.println(targetPos);
    
      Serial.print("Current Postion: ");
      Serial.println(currentPos);

      slave.write('0');  
  
      
    }  
  }

  
}

void encoder(){
  if(digitalRead(encoderPinB) == HIGH){
    currentPos++;
  }else{
    currentPos--;
  }
}

void x_manip(char key){
  switch(key){
    case '1':
      targetPos = -371 * 10;
      break;
    case '2':
      targetPos = -371 * 5;
      break;
    case '3':
      targetPos = 371 * 5;
      break;
    case '0':
      targetPos = 0;
      break;
  }

  x1 = round(0.2 * targetPos);
  x2 = round(0.6 * targetPos);
  x3 = round(0.2 * targetPos);

    
  //Speed control at different position
  //
  if (abs(targetPos - currentPos)> error && (targetPos > currentPos)) {
    if(currentPos <= x1){
      motor_speed = 255;
      MotorClockwise(motor_speed);
      delay(10);
      motor_speed = 127;
      MotorClockwise(motor_speed);
      Serial.print("x1: ");
      Serial.println(x1);
      Serial.print("motor speed: ");
      Serial.println(motor_speed);
    }
    
    else if(currentPos > x1 && currentPos <= x2+x1){
      motor_speed = 255;
      MotorClockwise(motor_speed);
      Serial.print("x2: ");
      Serial.println(x1+x2);
      Serial.print("motor speed: ");
      Serial.println(motor_speed);
    }
  
    else{
      motor_speed = 127;
      MotorClockwise(motor_speed);
      Serial.print("x3: ");
      Serial.println(x1+x2+x3);
      Serial.print("motor speed: ");
      Serial.println(motor_speed);
    }
  }

  else if (abs(targetPos - currentPos)> error && (targetPos < currentPos)){
    if(currentPos <= x1){
      motor_speed = 127;
      MotorCounterClockwise(motor_speed);
      
    }
    
    else if(currentPos > x1 && currentPos <= x2+x1){
      motor_speed = 255;
      MotorCounterClockwise(motor_speed);
      
    }
  
    else{
      motor_speed = 127;
      MotorCounterClockwise(motor_speed);
      Serial.print("end: ");
      Serial.print("motor speed: ");
      Serial.println(motor_speed);
    }
  }

  else {
    motor_speed = 0;
    MotorCounterClockwise(motor_speed);
    Serial.print("end: ");
    Serial.print("motor speed: ");
    Serial.println(motor_speed);
    if(start != 0){
      StepperMotor();
    }
    count++;
  }

  delay(100);

}

void MotorClockwise(int power){
  if(power >60){  // set the min value as 60 because of the motor inertia
    analogWrite(pin1, power);
    digitalWrite(pin2, LOW);
  }
  
  else{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}

void MotorCounterClockwise(int power){
  if(power > 60){
    analogWrite(pin2, power);
    digitalWrite(pin1, LOW);
  }
  
  else{
    digitalWrite(pin2, LOW);
    digitalWrite(pin1, LOW);
  }
}

void ServoMotor(){
  if(degree == 45){
    degree += 90 ;
    myServo.write(degree);                  // sets the servo position
    delay(15);                           // waits for the servo to get there
    start = 0; //goes back to origin
    for(int j = 0; j < 2; j++){
        tone(buzzerPin, note, 100);
        delay(300);
        noTone(buzzerPin);
    }
  }
  else if (degree == 135){
    degree -= 90;
    myServo.write(degree);                  // sets the servo position
    delay(15);                           // waits for the servo to get there */ 
    start = 2; //goes to collection window
  }
}

void StepperMotor(){
  if (y == 0){
    myStepper.step(-200);
    y += 5;
    ServoMotor();
  }
  else if (y == 5){
    myStepper.step(200);
    y -= 5;
    ServoMotor();
  }
}

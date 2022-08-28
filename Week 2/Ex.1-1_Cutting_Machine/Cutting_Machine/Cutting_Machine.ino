#include "pitches.h"

int pushButton = 2;
int toggleButton = 3;
int limitSwitch = 4;
int buzzerPin = 8;
int ledPin = 9;
int solenoidPin = 10;
int toggleState = 0;
int pushState = 0;
int limitState = 0;
int note = NOTE_A4;

void setup() {
  // put your setup code here, to run once:
  pinMode(pushButton, INPUT);
  pinMode(toggleButton, INPUT);
  pinMode(limitSwitch, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  toggleState = digitalRead(toggleButton);
  pushState = digitalRead(pushButton);
  limitState = digitalRead(limitSwitch);
  
  if (toggleState == LOW){ //when toggle switch is closed 
    digitalWrite(ledPin, LOW); //turn on the LED

    do{
      if(pushState == LOW && toggleState == LOW && limitState == HIGH){  //both switches are closed
        for(int i = 0; i < 10; i++){
          toggleState = digitalRead(toggleButton);  //update the voltage value of toggle switch
          limitState = digitalRead(limitSwitch);    //update the voltage value of limit switch
          if(limitState != HIGH || toggleState != LOW){  //if one of the switches is open
            if (limitState != HIGH) {  //if limit switch is open
              for(int j = 0; j < 3; j++){
                tone(buzzerPin, note, 100);
                delay(300);
                noTone(buzzerPin);
              }
              break;  
            }
            else{  //if toggle switch is open
              for(int j = 0; j < 3; j++){
                tone(buzzerPin, note, 100);
                delay(300);
                noTone(buzzerPin);
                digitalWrite(ledPin, HIGH);
              }
              break;
            }
          }
          
          else{  //in normal operation
            digitalWrite(solenoidPin, HIGH);
            delay(300);
            digitalWrite(solenoidPin, LOW);
            delay(300);
          }
        }  
      }
     }
     while(toggleState == 3);
  }
  else {
    digitalWrite(ledPin, HIGH); //turn off the LED
  }
}

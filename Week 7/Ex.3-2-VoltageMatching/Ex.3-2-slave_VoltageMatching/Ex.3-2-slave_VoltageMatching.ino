#include <SoftwareSerial.h>
#define RxD 11
#define TxD 10
int pinLED = 3;
int pinVolt = 5;
int voltage = 0;

char recvChar;                                        //variable to store character received
String recvStr;                                       //variable to store the series of received character

boolean blink;

SoftwareSerial slave(RxD, TxD);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                //start serial monitor, for communicating with the PC

  pinMode(RxD, INPUT);                               //set mode of receive pin (from bluetooth)
  pinMode(TxD, OUTPUT);                              //set mode of transmit pin (to bluetooth)
  slave.begin(9600);                                 //start the bluetooth serial "port"

  pinMode(pinLED, OUTPUT);                               //set led pin to output
  pinMode(pinVolt, INPUT);

  recvStr = "";                                      //initialize the string to be empty
}

void loop() {
  // put your main code here, to run repeatedly:
  if(slave.available()){
    
    recvChar = slave.read();
    
    recvStr = String(recvStr + String(recvChar));
 
    if((recvChar - 48) >= 0 && (recvChar - 48) < 10) {
      voltage *= 10; 
      voltage = ((recvChar - 48) + voltage);
    }
    
    else{
      if(voltage==analogRead(pinVolt)){
        digitalWrite(pinLED, HIGH);
        delay(200);
        digitalWrite(pinLED, LOW);
        slave.write("bingo");
      }
      Serial.println(voltage);
      voltage = 0;
      recvStr = "";
    } 
  }
}

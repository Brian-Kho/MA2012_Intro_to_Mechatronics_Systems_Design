#include <SoftwareSerial.h>
#define RxD 10
#define TxD 9

char recvChar;

SoftwareSerial slave(RxD, TxD);    //Slave arduino acts as a serial communication device

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                //start serial monitor, for communicating with the PC

  pinMode(RxD, INPUT);                               //set mode of receive pin (from bluetooth)
  pinMode(TxD, OUTPUT);                              //set mode of transmit pin (to bluetooth)
  slave.begin(9600);                                 //start the bluetooth serial "port"
}

void loop() {
  // put your main code here, to run repeatedly:
  if(slave.available()){
    recvChar = slave.read();
    if(recvChar=='1' || recvChar=='2'){
      Serial.print(recvChar);
      slave.write('0');  
    }  
  }
}

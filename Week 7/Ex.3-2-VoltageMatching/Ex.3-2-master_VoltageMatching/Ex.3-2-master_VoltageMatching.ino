#include <SoftwareSerial.h>
#define RxD 5
#define TxD 6
                                       //variable to store character received
SoftwareSerial master(RxD, TxD);                      //Master Arduino acts as a serial communication device

int potentPin = A0;

int voltage;

char recvChar;
String recvStr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                 //start serial monitor, for communicating with the PC

  pinMode(RxD, INPUT);                                //set mode of receive pin (from slave to master)
  pinMode(TxD, OUTPUT);                               //set mode of transmit pin (from master to slave)
  master.begin(9600);    
  
  pinMode(potentPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){  
    
      int count = 0;                   
      voltage = analogRead(potentPin);
      
      String vStr = String(voltage);
      char const *vChar = vStr.c_str();
      master.write(vChar);                          //it sends one byte each time, for chars, one alphabet is one byte, 
                                                      //if i want to send 'hello', it sends h first, then e, then l, and so on
                                                      //for int, 255 is one byte. maximum value i can send is 255, if i want to send 256, it sends as 0
                                                      //now the problem is how do i send '1023' as chars, if it sends one number by one number, how 
                                                      //do i concatenate back to '1023'?
      count += 1;
      if(count == 1){
        master.write('d');  
      }
      //Serial.println(vChar);
      delay(1);
    
  }
  if(master.available()){
    recvChar = master.read();
    Serial.print(recvChar);
    recvStr = String(recvStr + String(recvChar));  
  }
  else{
    if(recvStr=="bingo"){
      Serial.print('\n');
      recvStr = "";  
    }
  }
}

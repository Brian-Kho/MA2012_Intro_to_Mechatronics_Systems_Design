// include the library code:
#include <LiquidCrystal.h>

#include <string.h> 
using namespace std;

#include <SoftwareSerial.h>
#define RxD 8
#define TxD 9


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


SoftwareSerial master(RxD, TxD); //Master Arduino acts as a serial communication device


int pinToggle = A4; //pin to toggle switch


// Pins for 74C922 keypad encoder
int KB_DataAvailable=A5;//Data ready pin from Keyboard
int KB_A=10;
int KB_B=11;
int KB_C=12;
int KB_D=A3;

// Declare keypad layout
char keys[] = {'1','2','3','F',
               '4','5','6','E',
               '7','8','9','D',
               'A','0','B','C'};

char key;//selected key

int enter = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinToggle, INPUT);

  //initialize pins for keypad
  pinMode(KB_DataAvailable,INPUT);
  pinMode(KB_A,INPUT);
  pinMode(KB_B,INPUT);
  pinMode(KB_C,INPUT);
  pinMode(KB_D,INPUT);


  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);


  pinMode(RxD, INPUT);     //set mode of receive pin (from slave to master)
  pinMode(TxD, OUTPUT);    //set mode of transmit pin (from master to slave)
  master.begin(9600);    


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(pinToggle)==LOW){    
    lcd.setCursor(0, 0);
    lcd.print("Select 1 / 2");
    
    if(digitalRead(KB_DataAvailable)){
      KB_Read();
      if(enter==1){ //if key 'C' is pressed
        master.write(key);
      }
      lcd.setCursor(0, 1);
      lcd.print(key);
      delay(500);
    }

    if(master.available()){
      if(master.read()=='0'){
        lcd.clear();

        //5 cycles of flashing message
        for(int i=0; i<5; i++){
          lcd.setCursor(0, 1);
          lcd.print("Collect Item");
          delay(1000);
          lcd.clear();
          delay(500);
        }

        reset(); //goes back to standby mode
      }      
    }

    if(digitalRead(pinToggle)==HIGH){
      reset();
      break;  
    }
  }
}

void KB_Read() {
  int ka,kb,kc,kd;
  int k;
  ka=digitalRead(KB_A); //read encoder output A
  kb=digitalRead(KB_B); //read encoder output B
  kc=digitalRead(KB_C); //read encoder output C
  kd=digitalRead(KB_D); //read encoder output D

  k=ka+kb*2+kc*4+kd*8; // combine the encoder outputs 
  
  switch(k){
    case 0:
      key = keys[k]; // update the key with '1'
      Serial.println(key);
      break;

    case 1:
      key = keys[k]; // update the key with '2'
      Serial.println(key);
      break;

    case 15:
      enter = 1;
      //Serial.println(k);
      break;
  }
}

void reset(){
  lcd.clear();
  enter = 0;
  key = ' ';
}

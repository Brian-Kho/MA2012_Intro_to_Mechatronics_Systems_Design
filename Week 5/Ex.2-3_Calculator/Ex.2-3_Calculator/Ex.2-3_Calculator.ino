//This program reads a keypad and displays a LCD screen

// include the library code:
#include <LiquidCrystal.h>

#include <string.h> 
using namespace std;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Pins for 74C922 keypad encoder
int KB_DataAvailable=A5;//Data ready pin from Keyboard
int KB_A=10;
int KB_B=11;
int KB_C=12;
int KB_D=13;

// Declare keypad layout
char keys[] = {'1','2','3','F',
               '4','5','6','=',
               '7','8','9','/',
               '+','0','-','*'};

#define NO_OF_CHAR 8
char d[NO_OF_CHAR+1];//FIFO queue for characters to display

int v1 = 0;
int v2 = 0;
int ans = 0;
int op_pos;
char op;
int on=0;

void setup(void) {
  int i;
  for(i=0;i<NO_OF_CHAR;i++) d[i]=' ';
  d[NO_OF_CHAR]=0; // end with NULL
  //initialize pins for keypad
  pinMode(KB_DataAvailable,INPUT);
  pinMode(KB_A,INPUT);
  pinMode(KB_B,INPUT);
  pinMode(KB_C,INPUT);
  pinMode(KB_D,INPUT);

  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  Serial.begin(9600);
  }

void loop(void) {
  on=0;
  while(on==0){
    //check if the keypad is hit
    if(digitalRead(KB_DataAvailable)){
      KB_Read();
      lcd.setCursor(0, 1);
      if(on==0){
        lcd.print(d);
      }
      delay(500);
      for(int i=0; i<NO_OF_CHAR; i++){
        if(d[i]=='='){
          calculator(); 
          lcd.print(ans);
          v1 = 0;          // reset number 1
          v2 = 0;          // reset number 2
          ans = 0;
          op = ' ';         // reset the operator
          
          if(on==1){
            for(int j=0; j<NO_OF_CHAR+1; j++){
              d[j] = ' ';
            } 
            lcd.clear();
          }
        }
      }
      if(on==1){
        on=0;
        break;  
      }
    }
  }
}

void KB_Read() {
  int ka,kb,kc,kd,i;
  char k;
  ka=digitalRead(KB_A); //read encoder output A
  kb=digitalRead(KB_B); //read encoder output B
  kc=digitalRead(KB_C); //read encoder output C
  kd=digitalRead(KB_D); //read encoder output D

  k=ka+kb*2+kc*4+kd*8; // combine the encoder outputs 

  if(keys[k]=='F'){
    on = 1;  
  }
  else{
    on = 0;  
  }

  for(i=0;i<(NO_OF_CHAR-1);i++) d[i]=d[i+1];//move displayed characters in FIFO queue forward discarding the first one
  d[NO_OF_CHAR-1]=keys[k]; // update the key into the queue
  d[NO_OF_CHAR]=0; // end with NULL 
}

void calculator(){
  for(int i=0; i<NO_OF_CHAR; i++){
    if(d[i]=='+' || d[i]=='-' || d[i]=='*' || d[i]=='/'){
      op_pos = i;
      op = d[i];  
    }
  }

  for(int j=0; j<op_pos; j++){
    if((d[j]-48)>=0 && (d[j]-48)<10){
      v1 *= 10;
      v1 = v1 + (d[j]-48);
    }
  }
 
  for(int k=op_pos+1; k<NO_OF_CHAR; k++){
    if((d[k]-48)>=0 && (d[k]-48)<10){
      v2 *= 10;
      v2 = v2 + (d[k]-48);
    }
  }

  switch(op){
    case '+':
      ans = v1+v2;
      break;

    case '-':
      ans = v1-v2;
      break;

    case '*':
      ans = v1*v2;
      break;

    case '/':
      ans = round(v1/v2);
      break;
  }
  
  lcd.clear();
}

void reset_d() {
  for (int l = 0;l<(NO_OF_CHAR);l++) d[l] = ' ';
  d[NO_OF_CHAR] = 0;
}

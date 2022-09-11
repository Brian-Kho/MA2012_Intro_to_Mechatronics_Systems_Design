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

#define NO_OF_CHAR 7
char d[NO_OF_CHAR+1];//FIFO queue for characters to display

int v1, v2;
int ans;


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
    //check if the keypad is hit
    
    
    if(digitalRead(KB_DataAvailable)){
      
      KB_Read(); //read the keypad
      
      // set the cursor to column 0, line 1
      // (note: line 1 is the second row, since counting begins with 0):
      lcd.setCursor(0, 0);
      // print the KEY being pressed:
      lcd.print(d);
      delay(800);
    }
      
      
    
}

void calculator(){
  lcd.clear();
  int i;
  for(i=0; i<NO_OF_CHAR-1; i++){
   
    if (d[i] == '+' || d[i] == '-' || d[i] == '*' || d[i] == '/'){
      int j;
      for(j=0; j<i; j++){
        v1 *= 10;
        v1 = v1 + (d[j] - 48);
      }
      int k;
      for(k=i+1; k<NO_OF_CHAR; k++){
        v2 *= 10;
        v2 = v2 + (d[k] - 48);  
      }
      ans = v1 + v2;
      lcd.print(ans);
      
    }
    else{
      continue;  
    }
  }
  Serial.println(v1);
  Serial.println(v2);
  
}

void KB_Read() {
  int ka,kb,kc,kd,i;
  char k;
  ka=digitalRead(KB_A); //read encoder output A
  kb=digitalRead(KB_B); //read encoder output B
  kc=digitalRead(KB_C); //read encoder output C
  kd=digitalRead(KB_D); //read encoder output D

  k=ka+kb*2+kc*4+kd*8; // combine the encoder outputs 

  if(k == 7){
    lcd.clear(); 
    int i;
    for(i=0; i<NO_OF_CHAR-1; i++){
      d[i]--;
    }
    lcd.setCursor(0, 0);
    calculator();

  }
  else{
    for(i=0;i<(NO_OF_CHAR-1);i++) d[i]=d[i+1];//move displayed characters in FIFO queue forward discarding the first one
    d[NO_OF_CHAR-1]=keys[k]; // update the key into the queue
    d[NO_OF_CHAR]=0; // end with NULL
  }
  
 
}

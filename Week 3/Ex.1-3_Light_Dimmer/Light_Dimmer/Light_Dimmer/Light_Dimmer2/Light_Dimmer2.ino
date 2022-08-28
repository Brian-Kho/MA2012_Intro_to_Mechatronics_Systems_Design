int yellowLED = 6;
int redLED = 5;
int greenLED = 3;
int pinP = A0;
float val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(pinP, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(pinP);
  Serial.println(val);
  if(val < 255.75){
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW); 
    digitalWrite(greenLED, LOW);   
  }
  else if(val >= 255.75 && val < 511.5){
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW); 
    digitalWrite(greenLED, LOW);  
  }
  else if(val >= 511.5 && val < 767.25){
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH); 
    digitalWrite(greenLED, LOW);  
  }
  else{
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH); 
    digitalWrite(greenLED, HIGH);  
  }
}

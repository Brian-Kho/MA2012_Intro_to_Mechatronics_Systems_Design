int yellowLED = 6;
int redLED = 5;
int greenLED = 3;
int pinP = A0;
float val = 0;
float bright = 0;

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
  bright = val/4;
  analogWrite(yellowLED, bright);
  analogWrite(redLED, bright);
  analogWrite(greenLED, bright);
}

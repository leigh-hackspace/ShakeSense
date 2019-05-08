const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis 
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis
int Xoffset;
int Yoffset;
int Zoffset;
int RED = 12;
int GREEN = 11;
int YELLOW = 10;
int t1 = 500;

void setup() {
  Serial.begin(115200);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
  Xoffset = analogRead(xpin);
  Yoffset = analogRead(ypin);
  Zoffset = analogRead(zpin);
}

void loop() {
  
  Serial.print("X: ");
  Serial.print(analogRead(xpin)-(5));
  Serial.print("\t");
  
  //digitalWrite(RED,HIGH);
  //delay(t1);
  //digitalWrite(RED,LOW);
  //delay(t1);
  
  Serial.print("Y: ");
  Serial.print(analogRead(ypin)-(5));
  Serial.print("\t");
  
  //digitalWrite(GREEN,HIGH);
  //delay(t1);
  //digitalWrite(GREEN,LOW);
  //delay(t1);
  
  Serial.print("Z: ");
  Serial.print(analogRead(zpin)-(5));
  Serial.println();
  
  //digitalWrite(YELLOW,HIGH);
  //delay(t1);
  //digitalWrite(YELLOW,LOW);
  //delay(t1);
  // delay before next reading:
  delay(10);
}

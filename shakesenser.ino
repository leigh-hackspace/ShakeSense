#include <TimerOne.h>
#define maxArray 64
int a            = 0;   // in array
int Tick         = 0;
int ButtonPin    = 2;  //This is for the button to rest the tick 
bool isButtonPressed = false;
int sensorPinX   = A1;  // select the input pin for X Sensor
int sensorValueX = 0; // variable to store the value coming from the sensor
int offsetX      = 355;

int sensorPinY = A2;  // select the input pin for Y Sensor
int sensorPinZ = A3;  // select the input pin for Z Sensor

int sensorValueY = 0; // variable to store the value coming from the sensor
int sensorValueZ = 0; // variable to store the value coming from the sensor
int arrayHeadX = 0;   // start of the array
int arrayTailX = 0;   // end of the array
int arrayX[maxArray];       // array 
int ledPin = 13;      // select the pin for the LED

void setup() {
  Serial.begin(115200);
  Timer1.initialize(1000); // this value is in micro seconds (1000 Micro Seconds = 1 MilliSecond)
  Timer1.attachInterrupt(ReadSensors);
  pinMode(ButtonPin, INPUT);
 }

void ReadSensors(){
  
    // read the value from the sensors:
  Tick++; //counter for time
  arrayX[arrayHeadX] = analogRead(sensorPinX)-offsetX;
  arrayHeadX++;
  if (arrayHeadX > maxArray -1){ 
    arrayHeadX = 0;
    }

  if (arrayHeadX==arrayTailX){
    if(arrayHeadX > 0){
      arrayHeadX--;
      }
    else{
      arrayHeadX = 63;
    }
}
  //sensorValueY = analogRead(sensorPinY);
  //sensorValueZ = analogRead(sensorPinZ)-339;
}

void loop() {     //main loop
  //Serial.print("loops brother");
isButtonPressed =digitalRead(ButtonPin);
//Serial.println(digitalRead(ButtonPin));
//Serial.print(isButtonPressed + "Button pressed");
if (isButtonPressed){
  Serial.println("sensor reset");
  Tick = 0;
  delay(5000);
} 

while (Tick <= 6000000){ //tick is in micro seconds as it's in use in the interrupt 
  delay(100); // this vaule is in milliseconds
  Serial.print("X: ");
  for (a = 0;a < arrayHeadX;a++){
    Serial.print(arrayX[a]);
    Serial.println(", "); 
 }
 
}

 Serial.println("###");
 arrayHeadX= 0;  
}

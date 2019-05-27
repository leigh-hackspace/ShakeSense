#include <Adafruit_NeoPixel.h>
#define PIN_PXL 6

const int numReadings = 10;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN_PXL, NEO_RGBW + NEO_KHZ800);
const int groundpin = A3;             // analog input pin 4 -- ground
const int powerpin = A4;              // analog input pin 5 -- voltage
const int xpin = A2;                  // x-axis 
const int ypin = A1;                  // y-axis
const int zpin = A0;                  // z-axis

int Xoffset;
int Yoffset;
int Zoffset;

int YELLOW = 12;
int GREEN = 11;
int RED = 10;

float barAve = 0;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

/*
 * These are the activation tresh holds for the LEDs which is calculated from 
 * from the current value minus the previous vaule to get the difference 
 * e.g. A - B = C the threshold value is C
*/

const int RED_THRESHOLD = 75; 
const int YELLOW_THRESHOLD = 50;
const int GREEN_THRESHOLD = 25;

struct SensorValues

{

  int xValue;
  int yValue;
  int zValue;

  SensorValues()
    : xValue(0)
    , yValue(0)
    , zValue(0)
  {}

    int LengthSqr()

  {
   //a^2 = b^2 + c^2 + d^2
   return (xValue  * xValue) +  (yValue  * yValue) +  (zValue  * zValue);
  }

    SensorValues GetDifference( const SensorValues other ) const
  {
    SensorValues result;
    result.xValue = abs(xValue - other.xValue);
    result.yValue = abs(yValue - other.yValue);
    result.zValue = abs(zValue - other.zValue);
    return result;
  }  
  void Report()
  {

    Serial.print("X: ");
    Serial.print( xValue );
    Serial.print("\t");  
    Serial.print("Y: ");
    Serial.print( yValue );
    Serial.print("\t");  
    Serial.print("Z: ");
    Serial.print( zValue );
    Serial.print("\t\n");  
// PIXEL BAR ADDED BY Nemiah
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = zValue;
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }

   // calculate the average:
    average = total / numReadings;
    int bar = map(zValue,0,128,0,strip.numPixels());
    barAve = barAve - 0.1;
    if(bar > barAve) barAve = bar;
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      if(i < barAve) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
      } else {
        strip.setPixelColor(i, 0);
      }
     }
     for(uint16_t i=0; i<strip.numPixels(); i++) {
     if(i < bar) {
        //strip.setPixelColor(i, strip.Color(0, 255, 255));
      } else {
     }
     }
  }
};
// End of PIXEL BAR

SensorValues previousReading;
void setup() {  Serial.begin(115200);
 pinMode(groundpin, OUTPUT);
 pinMode(powerpin, OUTPUT);
 digitalWrite(groundpin, LOW);
 digitalWrite(powerpin, HIGH);
 Xoffset = analogRead(xpin);
 Yoffset = analogRead(ypin);
 Zoffset = analogRead(zpin);

 strip.begin();
  strip.show();
}
void set_led( int light, int intensity, int activationThreshold )
{
 if( intensity > ( activationThreshold * activationThreshold ) )
 {
   digitalWrite(light,HIGH);
 }
 else
 {
   digitalWrite(light,LOW);
 }
 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
void flash_led(SensorValues & newReading ){
 SensorValues difference = newReading.GetDifference(previousReading);
 previousReading = newReading;
 difference.Report();
 int intensity = difference.LengthSqr();
 set_led(RED,    intensity, RED_THRESHOLD);
 set_led(YELLOW, intensity, YELLOW_THRESHOLD);
 set_led(GREEN,  intensity, GREEN_THRESHOLD);
strip.show();
}
void loop() {
 SensorValues reading;
 reading.xValue = analogRead(xpin);
 reading.yValue = analogRead(ypin);
 reading.zValue = analogRead(zpin);
 flash_led(reading);
 // delay before next reading:
 delay(10);
}

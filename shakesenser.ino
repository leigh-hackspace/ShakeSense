const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis 
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis

int Xoffset;
int Yoffset;
int Zoffset;

int YELLOW = 12;
int GREEN = 11;
int RED = 10;

/*
 * These are the activation tresh holds for the LEDs which is calculated from 
 * from the current value minus the previous vaule to get the difference 
 * e.g. A - B = C the threshold value is C
*/
const int RED_THRESHOLD = 100; 
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
  }
};

SensorValues previousReading;

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
}

void flash_led(SensorValues & newReading ){

  SensorValues difference = newReading.GetDifference(previousReading);
  previousReading = newReading; 
  difference.Report();
  
  int intensity = difference.LengthSqr();

  set_led(RED,    intensity, RED_THRESHOLD);
  set_led(YELLOW, intensity, YELLOW_THRESHOLD);
  set_led(GREEN,  intensity, GREEN_THRESHOLD);
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

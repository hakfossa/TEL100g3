#include <GravityPump.h>
#define sensorPin A1

int val = 0;
int soilPin = A0;
const int pumpPin = 9;
GravityPump pump;

int red = 3;
int green = 5;
int blue = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pump.setPin(9);
  pump.getFlowRateAndSpeed();
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void water(){
    //pump.update();
    pump.pumpDriver(0, 3000);

  }
long moistureValue(){
  long soilValue;
  //delaåy(2000); //int(4.32*pow(10,7))
  soilValue = analogRead(soilPin);
  //delay(10000);
  return soilValue;
}

int readSensor() {
	delay(10);							// wait 10 milliseconds
	val = analogRead(sensorPin);		// Read the analog value form sensor
	//digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// send current reading
}

void setRGB(int redVal, int greenVal, int blueVal) {
  // sets intensity levels for each color of the RGB light. Values between 0 and 255
  analogWrite(red, redVal);
  analogWrite(green, greenVal);
  analogWrite(blue, blueVal);
}

void loop() {
 
  pump.update();
  Serial.println(moistureValue());
  
  if (moistureValue()>500){
    //Serial.println(moistureValue());
    water();
    Serial.println("watering");
    delay(5000); //time of watering
    pump.update();
    pump.stop();
    delay(1000);
    int level = readSensor();
	
	Serial.print("Water level: ");
	Serial.println(level);
  if (level <100){
    setRGB(150, 0, 0);
  }
  else if (level < 420){
    setRGB(150, 150, 150);
  }
  else{
    setRGB(150, 150, 0);
  }
    Serial.println("no water");
  }
  else if (moistureValue()<500){
    pump.stop();
}
delay(30000);//int(4.32*pow(10,7)) : 12 hours between mesrement
}

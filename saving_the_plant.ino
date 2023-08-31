#include <GravityPump.h>


#define sensorPin A1
int val = 0;
int soilPin = A0;
const int pumpPin = 9;
GravityPump pump;

//Pins for LED
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

//Pumps water
void water(){
    //pump.update();
    pump.pumpDriver(0, 3000);

  }

// Measures the moisture in the soil
long moistureValue(){
  long soilValue;
  //delaåy(2000); //int(4.32*pow(10,7))
  soilValue = analogRead(soilPin);
  //delay(10000);
  return soilValue;
}

//Measures the water level in the watertank
int readSensor() {
	delay(10);
	val = analogRead(sensorPin);
	return val;
}

// sets intensity levels for each color of the RGB light. Values between 0 and 255
void setRGB(int redVal, int greenVal, int blueVal) {
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
    delay(30000); //time of watering
    pump.update();
    pump.stop();
    delay(1000);
    int level = readSensor(); //Reads the water level in the tank after the olant has been watered
	
	Serial.print("Water level: ");
	Serial.println(level);
  if (level <100){  //Verry little water left in water tank
    setRGB(150, 0, 0);
  }
  else if (level < 420){ //Medium water level
    setRGB(255, 40, 0);
  }
  else{
    setRGB(150, 150, 0); //Enough water
  }
    Serial.println("no water");
  }
  else if (moistureValue()<500){
    pump.stop();
}
delay(30000);//int(4.32*pow(10,7)) : 12 hours between mesurement
}
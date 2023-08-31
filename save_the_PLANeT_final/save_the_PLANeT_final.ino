/* Code for Arduino UNO part of Save The PLANeT project. 
UNO and MKR1010 communicate through serial pins.
Messages wil consist of 3 charcters and any number of digits. 
The messages use "-" as a separator. The characters decide 
what will be done and the numbers are used to communicate 
numerical data if necessary */

// source for pin_serial related code: 
// https://forum.arduino.cc/t/how-to-choose-serial-port-as-variable/651607/9
HardwareSerial* pin_serial = NULL; // Serial variable 

#include <Servo.h>

// defining pin variables:
int soilPin = A0;
int waterLevelPin = A1;
const int pumpPin = 9;

// make an instance of Servo object, 
// the object is used to controll the pump
Servo pump;

// control pins for RGB LED:
int red = 3;
int green = 5;
int blue = 6;

// timer variable for 12 hour 
int hundredSecondsCompleted;

void setup() { 
  
  pin_serial = &Serial; // Set serial variable so comms fucntions will work
  
  
  // initialize serial:
  pin_serial -> begin(9600);
  
  // associate pin 9 with pump:
  pump.attach(pumpPin);
  

  pinMode(soilPin, INPUT);
  pinMode(waterLevelPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
}




void loop() {

  int soilMoisture;
  int soilMoisturePercentage; // mapped value from soil sensor
  String last_msg; // last message from mkr1010

  soilMoisture = readMoistureValue();
  

  soilMoisturePercentage = map(soilMoisture, 550, 260, 0, 100);
  sendSoilMoisture(soilMoisturePercentage);

  // check level and update LED/mkr1010
  checkWaterLevel();
  
  if (checkMessage()) { // check if anything in serial
    last_msg = recieveMessage();
  }

  if (last_msg.substring(0, 3) == "wtr") {
    // start forced watering sequence
    waterPlant();
  }

  if (hundredSecondsCompleted > 4) {
    // if ~12 hours has passed
    Serial.println("12 hour check");
    if (soilMoisture > 500) {
      waterPlant();
    }
    hundredSecondsCompleted = 0; // reset counter
  }

  // count + 1
  hundredSecondsCompleted += 1;

  // wait 100 seconds between each check of serial and sensors
  delay(10000); 

}

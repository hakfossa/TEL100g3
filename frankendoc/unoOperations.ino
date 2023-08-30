void setRGB(int redVal, int greenVal, int blueVal) {
  // sets intensity levels for each color of the RGB light. Values between 0 and 255
  analogWrite(red, redVal);
  analogWrite(green, greenVal);
  analogWrite(blue, blueVal);
}


void waterPlant() {
  // function that waters plant until its properly wet
  int moistureValue;
  while (moistureValue < 500) {
    pump.pumpDriver(0, 3000);
    delay(3000);
    pump.update();
    pump.stop();
    delay(1000);
    moistureValue = readWaterLevel();
  }
  
  sendMessage("wtd"); // send message watering done
}


int readWaterLevel() {
  // reads and returns current value of water level sensor
	int waterLevel;
	waterLevel = analogRead(waterLevelPin);		// Read the analog value form sensor
	return waterLevel;							// send current reading
}


void checkWaterLevel() {
  int waterLevel = readWaterLevel();

  if (waterLevel < 100){
    setRGB(150, 0, 0); // very low, red light
    sendMessage("wll"); //message mkr level is low
  }
  else if (waterLevel < 420){
    setRGB(150, 150, 0); // low, yellow light
  }
  else{
    setRGB(0, 255, 0); // all good green light
    sendMessage("wnl"); //message mkr level is not low
  }
  
}


long readMoistureValue(){
  // reads current value of soil moisture sensor
  long soilValue;
  soilValue = analogRead(soilPin);
  return soilValue;
}

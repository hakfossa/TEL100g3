void setRGB(int redVal, int greenVal, int blueVal) {
  // sets intensity levels for each color of the RGB light. Values between 0 and 255
  analogWrite(red, redVal);
  analogWrite(green, greenVal);
  analogWrite(blue, blueVal);
}

void stopPump() {
  pump.write(90);
}

void startPump() {
  pump.write(0);
}


void waterPlant() {
  // function that waters plant until its properly wet
  int moistureValue;
  digitalWrite(LED_BUILTIN, HIGH);
  while (moistureValue > 500) {
    startPump();
    delay(3000);
    moistureValue = readMoistureValue();
  }
  stopPump();
  digitalWrite(LED_BUILTIN, LOW);
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
    setRGB(250, 0, 0); // very low, red light
    sendMessage("wll"); //message mkr level is low
  }
  else if (waterLevel < 420){
    setRGB(255, 40, 0); // low, yellow light
    sendMessage("wll"); //message mkr level is low
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

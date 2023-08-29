/* Code for communication between MKR and UNO. Messages wil consist of 3 charcters and at least 5 digits. The characters decide what 
will be done and the numbers are to communicate numerical data if necessary */

// source for serial mode: https://forum.arduino.cc/t/how-to-choose-serial-port-as-variable/651607/9
HardwareSerial* pin_serial = NULL; // Serial variable 

int potPin = A0;
int buttonPin = 8;
int buttonPin2 = 4;
int ledPin = 7;
bool buttonReleased = true;
bool button2Released = true;

void setup() { 
  // comment out declaration based on arduino model used.
  pin_serial = &Serial; // For arduino uno
  //pin_serial = &Serial1; // For MKR1010
  
  
  pin_serial -> begin(9600);

  pinMode(buttonPin, OUTPUT);
  pinMode(buttonPin2, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  
}


void loop() {


  bool buttonValue; // check if button pressed
  bool button2Value; // check if button 2 pressed
  int potValue; // potentiometer read value
  int soilMoisturePercentage; // mapped value from soil sensor
  String last_msg;


  buttonValue = digitalRead(buttonPin);
  button2Value = digitalRead(buttonPin2);
  potValue = analogRead(potPin);
  soilMoisturePercentage = map(potValue, 0, 1023, 0, 100);
  

  if (checkMessage()) {
    last_msg = recieveMessage();
  }

  if (last_msg.substring(0, 3) == "wtr") {
    // start forced watering sequence
    digitalWrite(ledPin, HIGH);
    delay(10000);
    digitalWrite(ledPin, LOW);
    sendMessage("wtd"); // send message watering done

  }

  if (buttonValue && buttonReleased) { // check if first instance of pressed down
    String msg = "smp"; // smp = soil moisture percent, code for mkr to understand
    msg = msg + String(soilMoisturePercentage);
    sendMessage(msg);  
    buttonReleased = false;
  }

  else if(!buttonValue && !buttonReleased) {
    buttonReleased = true;
  }

  if (button2Value && button2Released) { // check if first instance of pressed down
    String msg = "wll"; // wll = water level low, code for mkr
    sendMessage(msg); 
    button2Released = false;
  }
  else if(!button2Value && !button2Released) {
    String msg = "wnl"; // wll = water not low, code for mkr
    sendMessage(msg);  
    button2Released = true;
  }


}

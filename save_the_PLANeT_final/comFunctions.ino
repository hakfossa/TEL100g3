

void sendMessage(String msg) {
  // sends the given message with a '-' at the end
  String msg_rdy = msg + "-";
  pin_serial -> print(msg_rdy);
}

bool checkMessage() {
  // checks if there is at least 8 characters in the serial to be read
  if (pin_serial -> available() >= 3) {
    return true;
  }
  else {
    return false;
  }
}

String recieveMessage() {
  // reads the first 8 characters in the serial and returns them as a string
  return pin_serial -> readStringUntil('-');

}

int getInt(String msg) {
  // fetches the numbers after the 3 chars
  
  return msg.substring(3).toInt();
}

void sendSoilMoisture(int soilMoisturePercentage) {
  String msg = "smp"; // smp = soil moisture percent, code for mkr to understand
  msg = msg + String(soilMoisturePercentage);
  sendMessage(msg); 
}


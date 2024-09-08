void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    String message = Serial.readStringUntil('\n');
    Serial.print("Arduino recieved: ");
    Serial.println(message);
  }
}

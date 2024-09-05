void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    float message = Serial.read();
    Serial.write(message);
  }
}

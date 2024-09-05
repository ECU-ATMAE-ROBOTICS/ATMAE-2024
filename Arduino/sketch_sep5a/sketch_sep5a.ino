void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    int message = Serial.read();
    
    Serial.print(message);
  }
}

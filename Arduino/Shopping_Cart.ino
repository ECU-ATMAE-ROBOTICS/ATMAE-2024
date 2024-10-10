#define LED_PIN 12

#include <ezButton.h>

#include <Servo.h>

int ind1;

int button_id;
double axis_val;
String receivedData = "";

int pos;


ezButton limitSwitch(13);
Servo leftservo;
Servo rightservo;

void parseData(String data);

void setup() {

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  limitSwitch.setDebounceTime(50);
  digitalWrite(LED_PIN, HIGH);
  leftservo.attach(4);
  rightservo.attach(3);
}

void loop() {
  if (Serial.available()) {
    char receivedChar = Serial.read();
    if (receivedChar == '\n') {  // Correct the newline character
      parseData(receivedData);
      receivedData = "";  // Clear the string after parsing
    } else {
      receivedData += receivedChar;  // Accumulate serial data into the string
    }
  }

  limitSwitch.loop();
  if (limitSwitch.isPressed()) {
    leftservo.write(90);
    rightservo.write(90);
    for (int i = 1; i < 16; i++) {
      digitalWrite(LED_PIN, HIGH);  // Turn LED on
      delay(250);
      digitalWrite(LED_PIN, LOW);   // Turn LED off
      delay(250);
    }
    digitalWrite(LED_PIN, HIGH);
  }

  if (button_id == 11) {
    // A button
    for (pos = 0; pos <= 90; pos += 1) {
      leftservo.write(pos);
      rightservo.write(pos);
      delay(15);
    }
  }


  if (button_id == 5){
    //X axis on Left Joystick
      if (axis_val == -1){
        leftservo.writeMicroseconds(1500); //90
        rightservo.writeMicroseconds(2000); //180
      }
      if (axis_val == 1){
        leftservo.writeMicroseconds(2000); //180
        rightservo.writeMicroseconds(1500); //90
      }
  }

  if (button_id == 9) {
    // Right Trigger
      leftservo.writeMicroseconds(2000); //180
      rightservo.writeMicroseconds(2000); //180
        if (axis_val == -1){
          leftservo.writeMicroseconds(1500); //90
          rightservo.writeMicroseconds(1500); //90
        }
  }

  if (button_id == 10) {
  // Left trigger
    leftservo.writeMicroseconds(1000); //0
    rightservo.writeMicroseconds(1000); //0
      if (axis_val == -1){
        leftservo.writeMicroseconds(1500); //90
        rightservo.writeMicroseconds(1500); //90
      }
  }

  if (button_id == 12){
    //B Button
    leftservo.writeMicroseconds(1500); //90
    rightservo.writeMicroseconds(1500); //90
  }


  button_id = 0;
  axis_val = 0;

}
void parseData(String data) {
    int splitIndex = data.indexOf(':');  // Find where the ';' is
    if (splitIndex != -1) {  // Ensure ';' exists in the data
        String buttonStr = data.substring(0, splitIndex);
        String axisStr = data.substring(splitIndex + 1);

        // Convert to int and double
        button_id = buttonStr.toInt();
        axis_val = axisStr.toDouble();

        // Debugging prints
        //Serial.print("Raw Data: ");
        Serial.println(data);
        //Serial.print("Button (as string): ");
        Serial.println(buttonStr);
        //Serial.print("Axis Value (as string): ");
        Serial.println(axisStr);
    } else {
        // Error handling if data doesn't contain ';'
        Serial.println("Error: Invalid data format. No ':' found.");
    }

    // Print the parsed values for debugging
    //Serial.print("Parsed Button: ");
    Serial.println(button_id);
    //Serial.print("Parsed Value: ");
    Serial.println(axis_val);
}

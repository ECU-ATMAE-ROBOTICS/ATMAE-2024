#define LED_PIN 11

#include <ezButton.h>

#include <Servo.h>

int ind1;

int button_id;
double axis_val;
double triggerValue;
double turnValue;

double LturnValue;
double RturnValue;

double LMotor;
double RMotor;

String receivedData = "";

int pos;
boolean Autonomous = false;


ezButton limitSwitch(12);
Servo leftservo;
Servo rightservo;

void parseData(String data);

void setup() {

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  limitSwitch.setDebounceTime(50);
  digitalWrite(LED_PIN, HIGH);
  leftservo.attach(2);
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

  //Freeze Button
  limitSwitch.loop();
  if (limitSwitch.isPressed()) {
    axis_val = 0;
    Serial.println("kys");

    leftservo.write(1500);
    rightservo.write(1500);
    
    for (int i = 1; i < 16; i++) {
      digitalWrite(LED_PIN, HIGH);  // Turn LED on
      delay(250);
      digitalWrite(LED_PIN, LOW);  // Turn LED off
      delay(250);
    }
    digitalWrite(LED_PIN, HIGH);
  }

  // if (button_id == 11) {
  //   // A button
  //   for (pos = 0; pos <= 90; pos += 1) {
  //     leftservo.write(pos);
  //     rightservo.write(pos);
  //     delay(15);
  //   }
  // }

  //Autonomous
  if (Autonomous){
    Serial.println("Auto");
    
    leftservo.write(1250);
    rightservo.write(1750);

    delay(4000);

    Serial.println("Auto Ended");
    leftservo.write(1500);
    rightservo.write(1500);

    Autonomous = false;
  }

  //*****This is to be tested, not sure if works****** */
  //Steers while moving
  if (triggerValue > 0.1 || triggerValue < -0.1){
    LMotor = 1500 - 500 * triggerValue * (1 - RturnValue);
    RMotor = 1500 + 500 * triggerValue * (1 - LturnValue);

  } 
  //Turn in place
  else if (button_id == 5){

    //Motors will both be set to the same value since they're inverted
    LMotor = 1500 + 500 * axis_val;
    RMotor = 1500 + 500 * axis_val;
  }

  leftservo.write(LMotor);
  rightservo.write(RMotor);



  // if (button_id == 12 && axis_val == 1.0) {
  //   //B Button
  //   Serial.println("Stopped");
  //   leftservo.writeMicroseconds(1500);   //90
  //   rightservo.writeMicroseconds(1500);  //90
  //}
}
void parseData(String data) {
  int splitIndex = data.indexOf(':');  // Find where the ';' is
  if (splitIndex != -1) {              // Ensure ';' exists in the data
    String buttonStr = data.substring(0, splitIndex);
    String axisStr = data.substring(splitIndex + 1);

    // Convert to int and double
    button_id = buttonStr.toInt();
    axis_val = axisStr.toDouble();

    //Throttle
    if (button_id == 10) {
      triggerValue = ((1 * (1 + axis_val)) / 2);
    } else if (button_id == 9) {
      triggerValue = -((1 * (1 + axis_val)) / 2);
    }

    //Turning
    if (button_id == 5) {
      
      //Left
      if (axis_val < 0) {
        RturnValue = -1 * axis_val;
        LturnValue = 0;
      
      //Right
      } else if (axis_val > 0) {
        LturnValue = axis_val;
        RturnValue = 0;

      //Straight
      } else {
        RturnValue = 0;
        LturnValue = 0;
      }
    }

    //Pause button on controller for Auto
    if(button_id == 22 && !Autonomous && axis_val == 1.0){
      axis_val = 0;
      Autonomous = true;
    }

    // Debugging prints
    //Serial.print("Raw Data: ");
    //Serial.println(data);
    //Serial.print("Button (as string): ");
    //Serial.println(buttonStr);
    //Serial.print("Axis Value (as string): ");
    //Serial.println(axisStr);
  } else {
    // Error handling if data doesn't contain ';'
    Serial.println("Err");
  }

  // Print the parsed values for debugging
  //Serial.print("Parsed Button: ");
  //Serial.println(button_id);
  //Serial.print("Parsed Value: ");
  //Serial.println(axis_val);
}

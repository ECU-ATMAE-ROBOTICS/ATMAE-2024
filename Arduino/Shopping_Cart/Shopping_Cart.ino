//ssh ubuntu@192.168.0.157
// 192.168.0.228
//port 9000

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

double LMotor = 1500;
double RMotor = 1500;

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
  //Read From Serial
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
    //Serial.println("kys");

    leftservo.write(1500);
    rightservo.write(1500);

    //Flash Button
    for (int i = 1; i < 16; i++) {
      digitalWrite(LED_PIN, HIGH);  // Turn LED on
      delay(250);
      digitalWrite(LED_PIN, LOW);  // Turn LED off
      delay(250);
    }
    digitalWrite(LED_PIN, HIGH);
    delay(15);
    Serial.println(limitSwitch.isPressed());
  }

  //Autonomous
  if (Autonomous) {
    Serial.println("Auto");

    //Move Forwards
    leftservo.write(1750);
    rightservo.write(1250);

    delay(2000);

    //Stop
    Serial.println("Auto Ended");
    leftservo.write(1500);
    rightservo.write(1500);

    if (limitSwitch.isPressed()) {

      leftservo.write(1500);
      rightservo.write(1500);

      //Flash Button
      for (int i = 1; i < 16; i++) {
        digitalWrite(LED_PIN, HIGH);  // Turn LED on
        delay(250);
        digitalWrite(LED_PIN, LOW);  // Turn LED off
        delay(250);
      }
      digitalWrite(LED_PIN, HIGH);
      delay(15);
      Serial.println(limitSwitch.isPressed());
    }

    Autonomous = false;
  }

  //Steers while moving
  if (triggerValue > 0.1 || triggerValue < -0.1) {
    LMotor = 1500 - 500 * triggerValue * (1 - RturnValue);
    RMotor = 1500 + 500 * triggerValue * (1 - LturnValue);

    leftservo.write(LMotor);
    rightservo.write(RMotor);
  }
  //Turn in place
  else if (button_id == 5) {

    //Motors will both be set to the same value since they're inverted
    LMotor = 1500 + 500 * axis_val;
    RMotor = 1500 + 500 * axis_val;
    
    leftservo.write(LMotor);
    rightservo.write(RMotor);
  } else {
    leftservo.write(1500);
    rightservo.write(1500);
  }
}

//Parses the instuction recieved from the Pi
void parseData(String data) {
  int splitIndex = data.indexOf(':');  // Find where the ';' is
  if (splitIndex != -1) {              // Ensure ';' exists in the data
    String buttonStr = data.substring(0, splitIndex);
    String axisStr = data.substring(splitIndex + 1);

    // Convert to int and double
    button_id = buttonStr.toInt(); //ID of the input
    axis_val = axisStr.toDouble(); //Value of the input

    //Forwards (RightTrigger)
    if (button_id == 10) {
      triggerValue = ((1 * (1 + axis_val)) / 2);
    } 
    //Reverse (Left Trigger)
    else if (button_id == 9) {
      triggerValue = -((1 * (1 + axis_val)) / 2);
    }

    //Turning (Left-Stick X axis)
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
    if (button_id == 22 && !Autonomous && axis_val == 1.0) {
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
  Serial.println(axis_val);
}

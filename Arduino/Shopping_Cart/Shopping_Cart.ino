#define LED_PIN 12

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


ezButton limitSwitch(11);
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

  limitSwitch.loop();
  if (limitSwitch.isPressed()) {
    leftservo.write(90);
    rightservo.write(90);
    Serial.println("kys");
    for (int i = 1; i < 16; i++) {
      digitalWrite(LED_PIN, HIGH);  // Turn LED on
      delay(250);
      digitalWrite(LED_PIN, LOW);   // Turn LED off
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

  //****Testing*****
    //Forwards
    LMotor = 1500 - 500 * triggerValue * (1 - RturnValue);
    RMotor = 1500 + 500 * triggerValue * (1 - LturnValue);

    //leftservo.write((1500 + 500 * triggerValue) - 500 * RturnValue);
    //rightservo.write((1500 - 500 * triggerValue) + 500 * LturnValue);

    leftservo.write(LMotor);
    //Serial.print(" ");
    rightservo.write(RMotor);

  // if (button_id == 12){
  //   //B Button
  //   leftservo.writeMicroseconds(1500); //90
  //   rightservo.writeMicroseconds(1500); //90
    
  // }
}
void parseData(String data) {
    int splitIndex = data.indexOf(':');  // Find where the ';' is
    if (splitIndex != -1) {  // Ensure ';' exists in the data
        String buttonStr = data.substring(0, splitIndex);
        String axisStr = data.substring(splitIndex + 1);

        // Convert to int and double
        button_id = buttonStr.toInt();
        axis_val = axisStr.toDouble();

        if (button_id == 10){
          triggerValue = ((1* (1+axis_val))/2);
        }
        else if(button_id == 9){
          triggerValue = -((1* (1+axis_val))/2);
        }


        if (button_id == 5) {
          //turnValue = axis_val;

          //***Testing****
          if(axis_val < 0){
            RturnValue = -1 * axis_val;
            LturnValue = 0;
          }
          else if (axis_val > 0){
            LturnValue = axis_val;
            RturnValue = 0;
          }
          else{
            RturnValue = 0;
            LturnValue = 0;
          }
          

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
        Serial.println("Error");
    }

    // Print the parsed values for debugging
    //Serial.print("Parsed Button: ");
    //Serial.println(button_id);
    //Serial.print("Parsed Value: ");
    //Serial.println(axis_val);
}

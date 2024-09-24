// Button1 = 1
// Button2 = 2
// Button3 = 3
// Button4 = 4
// Button5 = 5
// Button6 = 6
// Button7 = 7
// Button8 = 8
// Button9 = 9
// Button10 = 10
// Axis0 = 11
// Axis1 = 12
// Axis2 = 13
// Axis3 = 14
// Axis4 = 15
// Axis5 = 16
// Dpad0 = 17
// Dpad1 = 18
// Dpad2 = 19
// Dpad3 = 20

#define LED_PIN 12

#include <ezButton.h>

#include <Servo.h>

int ind1;

int button_id;

int button_val;

int pos;

float axis_val;

ezButton limitSwitch(13);
Servo leftMotor;
Servo rightMotor;


void setup() {

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  limitSwitch.setDebounceTime(50);
  digitalWrite(LED_PIN, HIGH);
  leftMotor.attach(3);
  rightMotor.attach(2);

}

void loop() {
  // put your main 98code here, to run repeatedly:
  //if (Serial.available())  {
    
  if (Serial.available()){
    String message = Serial.readStringUntil('\n');
    Serial.print("Arduino recieved: ");
    Serial.println(message);
  }
  
    // TODO

    //ind1 = readString.indexOf(',');  
    //button_id = readString.substring(0, ind1).toInt(); 

      //if (button_id < 11){    
        //button_val = readString.substring(ind1+1).toInt();
      //}
      
      //else{
        //axis_val = readString.substring(ind1+1).toFloat();
      //}
    //}
  //}

  limitSwitch.loop();
  if(limitSwitch.isPressed()){
    for (int i = 1; i < 16; i++){
      digitalWrite(LED_PIN, HIGH); // Turn LED on
      delay(250);                  // Wait for 300 ms
      digitalWrite(LED_PIN, LOW);  // Turn LED off
      delay(250);                  // Wait for 300 ms (added delay)
    }

    digitalWrite(LED_PIN, HIGH);
  }
  
  // for (pos = 0; pos <= 180; pos += 1) { 
  //   leftMotor.write(pos);   
  //   rightMotor.write(pos);              
  //   delay(15);                      
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { 
  //   leftMotor.write(pos);   
  //   rightMotor.write(pos);              
  //   delay(15);                       
  // }


  // if(button_id == 1){
      //A button
  // for (pos = 0; pos <= 180; pos += 1) { 
  //   leftMotor.write(pos);   
  //   rightMotor.write(pos);              
  //   delay(15);                      
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { 
  //   leftMotor.write(pos);   
  //   rightMotor.write(pos);              
  //   delay(15);                       
  // }
  // }

  // if(button_id == 2){

  // }

  // if(button_id == 3){

  // }

  // if(button_id == 4){
    
  // }

  // if(button_id == 5){

  // }

  // if(button_id == 6){
    
  // }


  // if(button_id == 7){

  // }

  // if(button_id == 8){
    
  // }


  // if(button_id == 9){

  // }

  // if(button_id == 10){
    
  // }

  // if(button_id == 11){
  //Axis 1 (x value on left stick)    
  //   if (axis_val > .3){
  //       leftservo.write(90);
  //       delay(15);
  //     }
  //     else (axis_val < -.30){
  //       rightservo.write(90);
  //       delay(15;)
  //     }
  // // }

  // if(button_id == 12){
    
  // }


  // if(button_id == 13){

  // }

  // if(button_id == 14){
    
  // }

  // if(button_id == 15){
      //Axis 4 (right trigger)
      // if (axis_val > .7){
      //   leftservo.write(180);
      //   rightservo.write(180);
      //   delay(15);
      // }
      // else if (axix_val > .5){
      //   leftservo.write(90);
      //   rightservo.write(90);
      //   delay(15);
      // }
      // else if (axis > .3){
      //   leftservo.wrtie(45);
      //   rightservo.write(45);
      //   delay(15);
      // }

  // }

  // if(button_id == 16){
    
  // }

  // if(button_id == 17){

  // }

  // if(button_id == 18){
    
  // }

  // if(button_id == 19){

  // }

  // if(button_id == 20){
    
  // }

  //axis_val = 0;
  //button_val = 0;
  //button_id = 0;

}


// #include <Servo.h>

// Servo leftMotor;
// Servo rightMotor;

// float y_value = 0;
// float x_value = 0;

// void setup() {
//     Serial.begin(9600);
//     leftMotor.attach(5);  // Pin for left motor
//     rightMotor.attach(6);  // Pin for right motor
// }

// void loop() {
//     if (Serial.available()) {
//         String input = Serial.readString();
//         int separatorIndex = input.indexOf(':');
//         int buttonID = input.substring(0, separatorIndex).toInt();
//         float value = input.substring(separatorIndex + 1).toFloat();

//         if (buttonID == 0) {
//             // Y-axis data (forward/backward)
//             y_value = value;
//         } else if (buttonID == 1) {
//             // X-axis data (turning)
//             x_value = value;
//         }

//         // Calculate motor speeds based on joystick values
//         float left_motor_speed = y_value + x_value;
//         float right_motor_speed = y_value - x_value;

//         // Control the motors
//         controlMotor(leftMotor, left_motor_speed);
//         controlMotor(rightMotor, right_motor_speed);
//     }
// }

// void controlMotor(Servo &motor, float value) {
//     int motorSpeed = map(value * 100, -100, 100, 0, 180);  // Map value to servo range
//     motor.write(motorSpeed);
// }

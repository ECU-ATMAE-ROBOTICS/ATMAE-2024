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

int ind1;

int button_id;

int button_val;

float axis_val;


void setup() {

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())  {
    
    // TODO

    ind1 = readString.indexOf(',');  
    button_id = readString.substring(0, ind1).toInt(); 

      if (button_id < 11){    
        button_val = readString.substring(ind1+1).toInt();
      }
      
      else{
        axis_val = readString.substring(ind1+1).toFloat();
      }
    }
  }

  if(limit_switch = pressed){

    blinnk
    wait 15 secs

  }

  if(button_id == 1){

  }

  if(button_id == 2){

  }

  if(button_id == 3){

  }

  if(button_id == 4){
    
  }

  if(button_id == 5){

  }

  if(button_id == 6){
    
  }


  if(button_id == 7){

  }

  if(button_id == 8){
    
  }


  if(button_id == 9){

  }

  if(button_id == 10){
    
  }

  if(button_id == 11){

  }

  if(button_id == 12){
    
  }


  if(button_id == 13){

  }

  if(button_id == 14){
    
  }

  if(button_id == 15){

  }

  if(button_id == 16){
    
  }

  if(button_id == 17){

  }

  if(button_id == 18){
    
  }

  if(button_id == 19){

  }

  if(button_id == 20){
    
  }


}

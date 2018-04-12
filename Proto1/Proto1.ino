#include <Smartcar.h>

Odometer encoderLeft, encoderRight;
Gyroscope gyro;
Car car;
char action;

const int TRIG_PIN = 6;
const int ECHO_PIN = 5;
Sonar frontSonar;
int i = 0;
char mode;


void setup() {
  Serial.begin(9600);
  frontSonar.attach(TRIG_PIN, ECHO_PIN);
  gyro.attach();
  encoderLeft.attach(2);
  encoderRight.attach(3);
  encoderLeft.begin();
  encoderRight.begin();
  car.begin(encoderLeft, encoderRight,gyro);
  gyro.begin();
  action = 0;
}

void loop() {

  /* manual_mode();
  }

void manual_mode(){*/
    while(Serial.available() > 0){
    //int action = interpretInput(Serial.read());

    action = Serial.read();
    switch(action){
  
    case 'f' : //Forward 
      moveDstyle(3);
      
    case 'b' : //Backwards
      moveDstyle(-3);

    case 'l' : // rotate left
      rotateDstyle(3);
      
    case 'r' : // rotate right
      rotateDstyle(-3);

      case 'm' :// mode change
      //Should call the autonomous mode function.
      break;

    /*case 5 // forward, rotate right
      move_rotate(int moveDir, int rotateDir);
      break;

    case 6 // forward, rotate left
      move_rotate(int moveDir, int rotateDir);
      break;

    case 7 // back, rotate right
      move_rotate(int moveDir, int rotateDir);
      break;

    case 8 // back, rotate left
      move_rotate(int moveDir, int rotateDir);
      break;
      */
    
  }
  }
}

  /*int interpretInput(String input){
    if(input == "m"){
      return 9;
    }
    
    else if(input.charAt(0) == "f"){// move forward++;
      if(input == "f"){ //move forward
        return 1;
      }
      
      else if(input == "fr"){ // rotate right and go forward
        return 5;
      }

      else if(input == "fl"){// rotate left and go forward
        return 6;
      }
      
    }

    else if(input.charAt(0) == "b"){ // move backwards++;
      if(input =="b"){ // move back.
        return 2;
      }

      else if(input == "br"){ // rotate right and go back
        return 7;
      }

      else if(input == "bl"){ // rotate left and go back

        return 8;
      }
    }

    else if(input == "l"){ // Rotate left.
      return 3;
    }
    
    else if(input == "r"){ // Rotate right.
      return 4;
    }
  }*/
  

  void moveDstyle(int dir){
    if(NoCrashDstyle() && dir > 0){
    car.go(dir);
    }
   else {
      car.go(dir);
    }
  }

  void rotateDstyle(int dir){
    car.rotate(dir);
  }
  void move_rotate(int moveDir, int rotateDir){
    if(NoCrashDstyle()){
    car.go(moveDir);
    }
    car.rotate(rotateDir);
  }
  
  boolean NoCrashDstyle(){ //Experimental
  if(frontSonar.getDistance() > 0 && frontSonar.getDistance()< 15){
    return false;
  }
  return true;
}

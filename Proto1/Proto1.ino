#include <Smartcar.h>

Odometer encoderLeft, encoderRight;
Gyroscope gyro;
Car car;

const int TRIG_PIN = 6;
const int ECHO_PIN = 5;
Sonar frontSonar;
int i = 0;


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
}

void loop() {
String input = "a"; // Have to 

manual_mode(input);

}

  void manual_mode(String input){
    
switch(input){
  
  case "a" : //Forward 
  moveDstyle(1);
  break;

  case "b" : //Backwards
  moveDstyle(-1);
  break;

  case "c" : // rotate left
  rotateDstyle(int dir);
  break;

  case "d" : // rotate right
  rotateDstyle(int dir);
  break;

  case "" // forward, rotate right
  move_rotate(int moveDir, int rotateDir);
  break;

  case "" // forward, rotate left
  move_rotate(int moveDir, int rotateDir);
  break;

  case "" // back, rotate right
  move_rotate(int moveDir, int rotateDir);
  break;

  case "" // back, rotate left
  move_rotate(int moveDir, int rotateDir);
  break;
  
  } 
    
  }
  

  void moveDstyle(int dir){
    if(NoCrashDstyle() && dir > 0){
    car.go(dir);
    }
    else if (NoCrashBack()){
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
  if(frontSonar.getDistance() >0 && frontSonar.getDistance()< 15){
    return false;
  }
  return true;
}

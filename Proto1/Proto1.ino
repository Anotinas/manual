#include <Smartcar.h>

Odometer encoderLeft, encoderRight;
Gyroscope gyro;
Car car;
Sonar frontSonar;

const int TRIG_PIN = 6;
const int ECHO_PIN = 5;
char mode;
char action;


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

    while(Serial.available() > 0){
    //int action = interpretInput(Serial.read());

    action = Serial.read();
    manual_mode();
  }
}

void manual_mode(){
  
    switch(action){
    case 'f' : //Forward 
      moveDstyle(3);
      
    case 'b' : //Backwards
      moveDstyle(-5);

    case 'r' : // rotate right
      rotateDstyle(5);
      
    case 'l' : // rotate left
      rotateDstyle(-5);

      case 'm' :// mode change
      //Should call the autonomous mode function.
      break; 
  }
  
}
  

  void moveDstyle(int dir){
    if(NoCrashDstyle() && dir > 0){
    car.setSpeed(50);
    }
   else {
      car.setSpeed(-50);
    }
  }

  void rotateDstyle(int dir){
    car.setAngle(dir);
  }
  
  boolean NoCrashDstyle(){ //Experimental
  if(frontSonar.getDistance() > 0 && frontSonar.getDistance()< 15){
    return false;
    car.stop;
  }
  return true;
}

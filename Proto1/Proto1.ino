#include <Smartcar.h>

Odometer encoder, encoderRight;
Gyroscope gyro;
Car car;
Sonar ultrasonicSensor;

const int TRIGGER_PIN = 6;
const int ECHO_PIN = 5;

// these has to be added  to the main code file.
char mode;
char action;


void setup() {
  Serial3.begin(9600);
  
  ultrasonicSensor.attach(TRIGGER_PIN, ECHO_PIN);
  gyro.attach();
  encoder.attach(2);
  //encoderRight.attach(3);
  encoder.begin();
  //encoderRight.begin();
  gyro.begin();
  car.begin(encoder ,gyro); // Check with the others if we should replace their begin.
  
  // Add these.
  action = 0; 
  mode = 'm';
}

void loop() {
  if(mode = 'm'){
    action = Serial3.read();
    
    switch(action){
      
    case 'f' : //Forward 
      moveDstyle(3);
      
    case 'b' : //Backwards
      moveBackwardsDstyle(-3);

    case 'r' : // rotate right
      rotateDstyle(5);
      
    case 'l' : // rotate left
      rotateDstyle(-5);

    case 'm' :// mode change
      mode = 'a';
      //car.setSpeed(0);
      car.stop();
      
    case 's' :
      //car.setSpeed(0);
      car.stop();  

    //default: car.stop(); // Might have to create another thing.
     //manual_mode();
    }
  }
  else {
    // Put in automatic mode and parking here.
  }
}

  void moveDstyle(int dir){
    if(NoCrashDstyle() && dir > 0){
    car.go(dir);
    }
  }

  void moveBackwardsDstyle(int dir){
    car.go(dir);
  }

  void rotateDstyle(int dir){
    car.rotate(dir);
  }
  
  boolean NoCrashDstyle(){
  if(ultrasonicSensor.getDistance() > 0 && ultrasonicSensor.getDistance()< 15){
    return false;
    //car.setSpeed(0);
  }
  return true;
}

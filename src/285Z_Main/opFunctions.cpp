#include "../include/285z/functions.hpp"
#include "../include/285z/initRobot.hpp"
#include "../include/285Z_Subsystems/tray.hpp"

bool anglerPositionBool = false;
bool intakeToggleBool = false;
bool liftPositionBool = false;
double liftPosReal = 0.0;
double liftPosReq = 0.0;
//           DRIVE         //
/*void tankDrive(){
  model->tank(controller.getAnalog(okapi::ControllerAnalog::rightY),
        controller.getAnalog(okapi::ControllerAnalog::leftY));

}

void arcadeDrive(){
  model->arcade(controller.getAnalog(okapi::ControllerAnalog::leftY),
    -controller.getAnalog(okapi::ControllerAnalog::rightX));
}*/


//******************* INTAKE ********************//

//Toggles intake
void toggleIntake(){
  if (intakeButton.changedToPressed())
  {
    intakeToggleBool = !intakeToggleBool;
  }
  else if(intakeToggleBool)
  {
    intake.setBrakeMode(AbstractMotor::brakeMode::coast);
    intake.moveVelocity   (600);
  }
  else
  {
    intake.moveVelocity	(0);
    intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
}

//Reverse intake
void intakeRev(){
  if (outtakeButton.isPressed())
  {
    intake.moveVelocity (-150);
    intake.setBrakeMode(AbstractMotor::brakeMode::coast);
  } else {
    intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
}

//****************** ANGLER ********************//

Tray angler;

void anglerManual(){
  if(anglerUpButton.isPressed()){
    angler.moveVel(100);
  } else if(anglerDownButton.isPressed()){
    angler.moveVel(-100);
  } else if(!anglerUpButton.isPressed() && !anglerDownButton.isPressed()){
    angler.moveVel(0);
  }
}

void anglerUp() {
  //-1690 degrees
  //TODO: Change angler1 to angler when there are two motors
  if (trayButton.changedToPressed())
  {
    anglerMotor.moveAbsolute(1400, 600);
    pros::delay(200);
    anglerMotor.moveAbsolute(2000, 200);
    //anglerController->setTarget(1690);
    //anglerControllerLPID.setTarget(1690);
    //anglerControllerRPID.setTarget(1690);
  }
}

void anglerDown(){
  if (trayDownButton.changedToPressed())
  {
    anglerMotor.moveAbsolute(0, -100);
    //anglerControllerLPID.setTarget(0);
    //anglerControllerRPID.setTarget(0);
    //anglerController->setTarget(0);
  }
}

//******************** LIFT *******************//

//MANUAL liftup
void liftUp(){
  if(liftUpButton.isPressed()){
    liftMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
    liftMotor.moveVelocity(-100);
  } else if(!liftUpButton.isPressed()&&!liftDownButton.isPressed()){
    liftMotor.moveVelocity(0);
    liftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
}

//MANUAL liftdown
void liftDown(){
  if(liftDownButton.isPressed()){
    liftMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
    liftMotor.moveVelocity(100);
  } else if(!liftUpButton.isPressed()&&!liftDownButton.isPressed()){
    liftMotor.moveVelocity(0);
    liftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
}
//MANUAL DUAL CONTROL
void liftManual(){
  liftDown();
  liftUp();
}

void toggleLiftHeight(){
  if(liftToggleButton.changedToPressed()){
    if(liftPositionBool == false){
      liftMotor.moveAbsolute(100,100);
      liftPositionBool = !liftPositionBool;
    } else {
      liftMotor.moveAbsolute(-100,100);
      liftPositionBool = !liftPositionBool;

    }
  }
}

void liftPID(){

  liftPosReal =  liftMotor.getPosition();
  liftPosReq = 1600;
  if(liftPosReal < liftPosReq){
      liftMotor.moveVelocity(50);
    } else {
      liftMotor.moveVelocity(-50);
    }
}
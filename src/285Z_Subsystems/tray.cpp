#include "../include/285z/initRobot.hpp"
#include "../include/285Z_Subsystems/tray.hpp"
#include "../include/285z/functions.hpp"
//the PID works on a system where it has the max vertical distance as UP and the minimum as DOWN

const int DOWN = 0; //down is this
const int UP = 1; // max is this

const int LIFTUP = 2;

int trayHeightPos = 0;

double traykP = 0.00039; //tray P coefficient
double traykI = 0.00001; //tray K coefficient
double traykD = 0.00001; //tray D coefficient

auto anglerController = AsyncPosControllerBuilder().withMotor(anglerPort)
                        .withGains({traykP, traykI, traykD})
                        .build();

//this function will undisable the angler
void Tray::moveToUp(bool op){
  trayHeightPos = 1;
  intake.setBrakeMode(AbstractMotor::brakeMode::coast); //overrides intake to coast
  if(anglerController->isDisabled()){ // toggles intake to enabled
    anglerController->flipDisable();

  }
  anglerController->setTarget(4700); //sets the target angle

  if(!op){
    anglerController->waitUntilSettled(); //checks if its auton so no accidental movement
  }
}

void Tray::moveToDown(bool op){
  trayHeightPos = 0;
  intake.setBrakeMode(AbstractMotor::brakeMode::hold); //will hold cubes automatically
  if(anglerController->isDisabled()){
    anglerController->flipDisable();
  }
  anglerController->setTarget(0);
  if(!op){
    anglerController->waitUntilSettled();
  }
}

void Tray::deploy(bool op){
  anglerController->setMaxVelocity(200);
  anglerController->setTarget(500);
  if(!op){
    anglerController->waitUntilSettled();
  }
}

int Tray::getHeightPos(){
  return trayHeightPos;
}

void Tray::stopPID(){
  if(!(anglerController->isDisabled())){
    anglerController->flipDisable();
  }
  anglerMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
}

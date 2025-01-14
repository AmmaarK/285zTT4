#include "../include/285z/initRobot.hpp"
#include "../include/285Z_Subsystems/lift.hpp"
#include "../include/285Z_Subsystems/tray.hpp"

const int NUM_HEIGHTS = 3;
const int height0 = 5;
const int height1 = 1600; //for dunking, old is 1800
const int height2 = 2400;

const int heights[NUM_HEIGHTS] = {height0, height1, height2};
double liftkP = 0.004;
double liftkI = 0.000001;
double liftkD = 0.00009;
// Old vals kp = 0.001, kI = 0.0001, kd = 0.0001

int heightNow = 0;

auto liftController = AsyncPosControllerBuilder().withMotor(liftPort)
                        .build();

void Lift::liftToggle(Tray angler){
  if (liftUpButton.changedToPressed() && heightNow < NUM_HEIGHTS - 1) {
      // If the goal height is not at maximum and the up button is pressed, increase the setpoint
      // heightNow++;
      heightNow = 2;
      liftController->setTarget(heights[heightNow]);

    } else if (liftDownButton.changedToPressed() && heightNow > 0) {
      heightNow--;
      liftController->setTarget(heights[heightNow]);
      if (heightNow == 0){
        liftMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
        liftController->tarePosition();
      }

    }

}

void Lift::deploy(){
  Tray angler;

  intake.moveVelocity(-200);

  liftController -> setTarget(1550);
  pros::delay(900);
  liftController -> setTarget(30);
}

void Lift::moveTo(int target){
  liftController -> setTarget(target);
  liftController -> waitUntilSettled();
}

void Lift::move(int vel){
  liftMotor.moveVelocity(-vel);
  liftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

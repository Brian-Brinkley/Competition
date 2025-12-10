/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controller-config.cpp                                     */
/*    Author:       engineer2                                                 */
/*    Created:      12/8/2025                                                 */
/*    Description:  Functions that process controller inputs during the       */
/*                  Driver Control period                                     */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
  bool Controller1UpDownButtonsControlMotorsStopped = true;
  bool DrivetrainLNeedsToBeStopped_Controller1 = true;
  bool DrivetrainRNeedsToBeStopped_Controller1 = true;

  bool drivetrainFlipped = false;

  void flip(){
    drivetrainFlipped = !drivetrainFlipped;

    LeftDriveSmart.stop(coast);
    RightDriveSmart.stop(coast);
    Controller1.rumble("-");
    wait(50, msec);
  }

  // define a task that will handle monitoring inputs from Controller1
  int rc_auto_loop_function_Controller1() {

    Controller1.ButtonB.pressed(flip);

    int drivetrainLeftSideSpeed = 0;
    int drivetrainRightSideSpeed = 0;
    // process the controller input every 20 milliseconds
    // update the motors based on the input values
    while(true) {
      if(RemoteControlCodeEnabled) {
        
        // calculate the drivetrain motor velocities from the controller joystick axies
        // left = Axis3
        // right = Axis2
        if (drivetrainFlipped) {
          drivetrainLeftSideSpeed = -1 * Controller1.Axis2.position();
          drivetrainRightSideSpeed = -1 * Controller1.Axis3.position();
        }
        else {
          drivetrainLeftSideSpeed = Controller1.Axis3.position();
          drivetrainRightSideSpeed = Controller1.Axis2.position();
        }
        
        // check if the value is inside of the deadband range
        if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
        } else {
          // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
          DrivetrainLNeedsToBeStopped_Controller1 = true;
        }
        // check if the value is inside of the deadband range
        if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
          // check if the right motor has already been stopped
          if (DrivetrainRNeedsToBeStopped_Controller1) {
            // stop the right drive motor
            RightDriveSmart.stop();
            // tell the code that the right motor has been stopped
            DrivetrainRNeedsToBeStopped_Controller1 = false;
          }
        } else {
          // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
          DrivetrainRNeedsToBeStopped_Controller1 = true;
        }
      
        // only tell the left drive motor to spin if the values are not in the deadband range
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          LeftDriveSmart.spin(forward, drivetrainLeftSideSpeed, percent);
        }
        // only tell the right drive motor to spin if the values are not in the deadband range
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          RightDriveSmart.spin(forward, drivetrainRightSideSpeed, percent);
        }
        
        // check the ButtonUp/ButtonDown status to control MotorGroup2
        if (Controller1.ButtonUp.pressing() || Controller1.ButtonL2.pressing()) {
          MotorGroup2.spin(forward, 100, percent);
          Controller1UpDownButtonsControlMotorsStopped = false;
        } else if (Controller1.ButtonDown.pressing() || Controller1.ButtonR2.pressing()) {
          MotorGroup2.spin(reverse, 100, percent);
          Controller1UpDownButtonsControlMotorsStopped = false;
        } else if (!Controller1UpDownButtonsControlMotorsStopped) {
          MotorGroup2.stop();
          // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
          Controller1UpDownButtonsControlMotorsStopped = true;
        }
        if(Controller1.ButtonL1.pressing()){
          PistonA.set(false);
        } else if (Controller1.ButtonR1.pressing()) {
          PistonA.set(true);
        }
      }
      // wait before repeating the process
      wait(20, msec);
    }
    return 0;
  }
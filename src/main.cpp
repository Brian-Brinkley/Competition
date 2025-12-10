/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       engineer2                                                 */
/*    Created:      12/8/2025                                                 */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
    calibrateDrivetrain();
    selection.pressed(auton_selector);
    LeftDriveSmart.setPosition(0,degrees);
    RightDriveSmart.setPosition(0,degrees);
}



void usercontrol(void) {
    while (1) {
        rc_auto_loop_function_Controller1();
    }
}

int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(auton);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
    }
}

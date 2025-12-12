#include "vex.h"

using namespace vex;

void auton() {
    ErrorDrive errorDrive;
    if(finalChoice) {

    }
    else {
        Brain.Timer.reset();
        errorDrive.errorDist(50,1100);
        Drivetrain.turnToHeading(90,degrees);
        errorDrive.errorDist(50,285);
        MotorGroup2.spin(reverse,70,percent);
        wait(2,seconds);
        MotorGroup2.stop(coast);
        errorDrive.errorDist(-50,50);
        Drivetrain.turnToHeading(95, degrees);
        errorDrive.errorDist(-70,800);
        MotorGroup2.spin(reverse,100,percent);
        wait(2,seconds);
        MotorGroup2.stop(coast);
        Brain.Screen.print(Brain.Timer.time(seconds));
    }
}
#include "vex.h"

using namespace vex;

void auton() {
    ErrorDrive errorDrive;
    if(finalChoice) {

    }
    else {
        errorDrive.errorDist(50,1100);
        Drivetrain.turnToHeading(90,degrees);
        errorDrive.errorDist(50,275);
        MotorGroup2.spin(reverse,80,percent);
        wait(2,seconds);
        MotorGroup2.stop(coast);
        errorDrive.errorDist(-50,800);
        MotorGroup2.spin(reverse,80,percent);
        wait(2,seconds);
        MotorGroup2.stop(coast);
    }
}
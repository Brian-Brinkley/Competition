/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.cpp                                          */
/*    Author:       engineer2                                                 */
/*    Created:      12/8/2025                                                 */
/*    Description:  Robot hardware configurations                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

brain Brain;

controller Controller1;
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT12, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT10, ratio18_1, true);
motor rightMotorB = motor(PORT20, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial DrivetrainInertial = inertial(PORT14);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 345, 281, mm, 1);

motor MotorGroup2MotorA = motor(PORT2, ratio18_1, true);
motor MotorGroup2MotorB = motor(PORT8, ratio18_1, false);
motor MotorGroup2MotorC = motor(PORT7, ratio18_1, false);
motor MotorGroup2MotorD = motor(PORT13, ratio18_1, false);
motor_group MotorGroup2 = motor_group(MotorGroup2MotorA, MotorGroup2MotorB, MotorGroup2MotorC, MotorGroup2MotorD);

digital_out PistonA = digital_out(Brain.ThreeWirePort.A);
pot AutonSelector = pot(Brain.ThreeWirePort.B);
bumper selection = bumper(Brain.ThreeWirePort.C);

bool vexcode_initial_drivetrain_calibration_completed = false;

void calibrateDrivetrain(void){
    Brain.Screen.print("Calibrating");
    Brain.Screen.newLine();
    Brain.Screen.print("Inertial");
    DrivetrainInertial.calibrate();
    while(DrivetrainInertial.isCalibrating()){
        wait(200,msec);
    }
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
}
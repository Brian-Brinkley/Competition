using namespace vex;

extern brain Brain;

extern controller Controller1;
extern motor leftMotorA;
extern motor leftMotorB;
extern motor_group LeftDriveSmart;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor_group RightDriveSmart;
extern inertial DrivetrainInertial;
extern smartdrive Drivetrain;

extern digital_out PistonA;

extern motor MotorGroup2A;
extern motor MotorGroup2B;
extern motor MotorGroup2C;
extern motor MotorGroup2D;
extern motor_group MotorGroup2;

extern void auton_selector();
extern int rc_auto_loop_function_Controller1();
extern pot AutonSelector;
extern bumper selection;

extern bool vexcode_initial_drivetrain_calibration_completed;
extern void calibrateDrivetrain(void);
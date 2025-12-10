using namespace vex;

//Function class for errorDrive functions during the Autonomous period
class ErrorDrive {
    public:
    //Constant of correction
    float kP = 0.5;
    //Ratio of degrees rotated to mm travelled
    const double distRat = 0.88662726;
    public:
    template <typename Condition>
    void errorDrive(double baseSpeed, Condition condition){
        //Resets the drivetrain position
        LeftDriveSmart.setPosition(0, degrees);
        RightDriveSmart.setPosition(0, degrees);
        //Finds the target heading to drive to
        double targetHeading = DrivetrainInertial.heading(degrees);
        //Runs corrected driving while condition parameter is true
        while(condition()){
            //Finds the current heading
            double currentHeading = DrivetrainInertial.heading(degrees);
            //Finds the error
            double error = targetHeading - currentHeading;
            //Angle wrapping
            if(error > 180) error -= 360;
            if(error < -180) error += 360;
            //Calculates the correction
            double correction = error * kP;
            //Implements the correction
            double leftSpeed = baseSpeed + correction;
            double rightSpeed = baseSpeed - correction;
            //Applies the correction
            LeftDriveSmart.spin(forward, leftSpeed, percent);
            RightDriveSmart.spin(forward, rightSpeed, percent);
            wait(20,msec);
        }
        Drivetrain.stop(brake);
    }

    void errorDist(double baseSpeed, double dist){
            //Resets the drivetrain position
            LeftDriveSmart.setPosition(0,degrees);
            RightDriveSmart.setPosition(0,degrees);
            //Finds the heading and rotation
            double travelDist = dist * distRat;
            double targetHeading = DrivetrainInertial.heading(degrees);
            //Runs while the motors haven't rotated enough
            while(fabs(LeftDriveSmart.position(degrees)) < travelDist && fabs(RightDriveSmart.position(degrees)) < travelDist){
            //Finds the current heading
            double currentHeading = DrivetrainInertial.heading(degrees);
            //Finds the error
            double error = targetHeading - currentHeading;
            //Angle wrapping
            if(error > 180) error -= 360;
            if(error < -180) error += 360;
            //Calculates the correction
            double correction = error * kP;
            //Implements the correction
            double leftSpeed = baseSpeed + correction;
            double rightSpeed = baseSpeed - correction;
            //Applies the correction
            LeftDriveSmart.spin(forward, leftSpeed, percent);
            RightDriveSmart.spin(forward, rightSpeed, percent);
            wait(20,msec);
        }
        Drivetrain.stop(brake);
    }
};
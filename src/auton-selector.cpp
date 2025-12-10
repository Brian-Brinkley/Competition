/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton-selector.cpp                                        */
/*    Author:       engineer2                                                 */
/*    Created:      12/9/2025                                                 */
/*    Description:  Selector funtion for the Preautonomous period             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;


bool firstPress = false;
bool finalPress = false;
bool leftRight;
bool finalChoice = false;

void auton_selector() {
    
    if (!firstPress) {
        if (AutonSelector.angle(percent) < 50) {
            leftRight = true;
        }
        else {
            leftRight = false;
        }
        firstPress = true;

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("You have chosen: ");
        Brain.Screen.print(leftRight ? "Left" : "Right");
        Brain.Screen.newLine();
        Brain.Screen.newLine();
        Brain.Screen.print("Press bumper again to continue");

        return;
    }
    else if (!finalPress) {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Final Choice: ");
        Brain.Screen.print(leftRight ? "Left" : "Right");
        finalChoice = leftRight;
        finalPress = true;
        wait(2,seconds);
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
    }
}
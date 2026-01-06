#include "vex.h"

using namespace vex;

bool testDriver = false;

void testFunc() {
    if(finalPress && !testDriver) {
        wait(2,seconds);
        auton();
        testDriver = true;
        return;
    }  
    
}
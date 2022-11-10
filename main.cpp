// "Global Libraries" 
#include "hwlib.hpp"
#include "rtos.hpp"

// Local Include Files
#include "res/settings.hpp"
#include "Display/displayControl.hpp"
#include "Button/button.hpp"
#include "Button/buttonHandler.hpp"
#include "motionSensor/motionSensorHandler.hpp"

#include "ManageLightsControl.hpp"
#include "InitializeControl.hpp"


int main(){
    // HWLIB needs this 1 sec startup to get the console running
    hwlib::wait_ms(1000);

    smartLightSettings settings;
    DisplayControl dispControl;
    ButtonHandler buttHandler;
    MotionSensorHandler motionHandler;

    Button upButton(UPBUTTONID);
    Button downButton(DOWNBUTTONID);
    Button checkButton(CHECKBUTTONID);
    Button cancelButton(CANCELBUTTONID);


    ManageLightsControl lightController(
        settings,
        dispControl,
        upButton,
        downButton,
        checkButton,
        cancelButton,
        buttHandler,
        motionHandler
    );

    InitializeControl initController(
        settings,
        dispControl,
        upButton,
        downButton,
        checkButton,
        cancelButton,
        buttHandler
    );


    rtos::run();
};


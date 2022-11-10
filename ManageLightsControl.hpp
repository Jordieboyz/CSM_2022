// Local Include Files
#include "res/settings.hpp"
#include "Display/displayControl.hpp"
#include "Button/buttonHandler.hpp"
#include "motionSensor/motionSensorHandler.hpp"
#include "Lights/lightSensor.hpp"
#include "Lights/lights.hpp"


class ManageLightsControl : public rtos::task<>, 
                            public ButtonListener, 
                            public motionListener {

public:

    void manageLights() { 
        manageLightsFlag.set(); 
    };
 
    void motionIsDetected(int motionSensID) {
        motionDetectionPool.write(motionSensID);
        motionDetectedFlag.set();
    };

    void buttonPressed(int buttonID) { 
        bPressedChannel.write(buttonID); 
    };

    ManageLightsControl(smartLightSettings &sets,
                        DisplayControl &dispControl,
                        Button &upBut,
                        Button &downBut,
                        Button &checkBut,
                        Button &cancelBut,
                        ButtonHandler &butHandler,
                        MotionSensorHandler &motionHandler ) :

        task(1, "manageLightsControl"),
        manageLightsFlag(this),
        motionDetectedFlag(this),
        motionDetectionPool("motionDetectionPool"),
        bPressedChannel(this),


        settings(sets),
        displayController(dispControl),
        upButton(upBut),
        downButton(downBut),
        checkButton(checkBut),
        cancelButton(cancelBut),

        mSens1_living(1),
        mSens2_kitchen(2),
        mSens3_bathroom(3),
        mSens4_bedroom(4)
    {
        butHandler.addButton(&upBut);
        butHandler.addButton(&downBut);
        butHandler.addButton(&checkBut);
        butHandler.addButton(&cancelBut);

        upButton.addButtonListener(this);
        downBut.addButtonListener(this);
        checkBut.addButtonListener(this);
        cancelBut.addButtonListener(this);

        mSens1_living.addMotionListener(this);
        mSens2_kitchen.addMotionListener(this);
        mSens3_bathroom.addMotionListener(this);
        mSens4_bedroom.addMotionListener(this);

    }

private:

    // States
    enum state_t { WAIT = 0, CHOOSE_SETTING, CHANGE_SETTING};
    state_t state = WAIT;
    state_t prev_state = WAIT;
    
    // rtos waitables
    rtos::flag manageLightsFlag;
    rtos::flag motionDetectedFlag;
    rtos::pool<int> motionDetectionPool;
    rtos::channel<int, 12> bPressedChannel;
    
    // STD specific variables
    selectableSettings currSelected;
    screen currScreen = screen::startInitializeScreen;
    int bPressedID = -1;

    LightSensor lightSens;
    LightControl lightController;

    smartLightSettings& settings;
    DisplayControl& displayController;

    Button& upButton;
    Button& downButton;
    Button& checkButton;
    Button& cancelButton;

    MotionSensor mSens1_living;
    MotionSensor mSens2_kitchen;
    MotionSensor mSens3_bathroom;
    MotionSensor mSens4_bedroom;
    

    void main() override {
        while(true){
            switch (state){
                case WAIT :
                {

                    wait(manageLightsFlag);

                    // Check which mode we are in
                    if( settings.getSetting(str(Mode)) == modes::Manual){
                        currScreen = screen::manualManageLightsScreen;
                        currSelected = manualSettings(); 
                        
                        prev_state = state;
                        state = CHOOSE_SETTING;
                    } else {
                        // STATE FOR AUTOMATIC???
                    }
                break;   
                }
                case CHOOSE_SETTING :
                {
                    // prevent writing the whole screen everytime you use the up or downbutton
                    if(prev_state != state){
                        displayController.showScreen(currScreen);
                    }
                    displayController.showSelector(currSelected);

                    wait(bPressedChannel);

                    bPressedID = bPressedChannel.read();

                    if( bPressedID == UPBUTTONID ){
                        currSelected++;
                        prev_state = state;
                        state = CHOOSE_SETTING;
                    }
                    else if( bPressedID == DOWNBUTTONID){
                        currSelected--;
                        prev_state = state;
                        state = CHOOSE_SETTING;
                    }
                    else if(bPressedID == CHECKBUTTONID){
                        prev_state = state;
                        state = CHANGE_SETTING;
                    } 
                    else if(bPressedID == CANCELBUTTONID) {
                        prev_state = state;
                        state = WAIT;
                    }
                break;
                }
                case CHANGE_SETTING :
                {
                    Setting* curr = settings.at(currSelected);

                    wait(bPressedChannel);

                    bPressedID = bPressedChannel.read();

                    if( bPressedID == UPBUTTONID ){
                        if(curr->name == str(Brightness)){
                            curr->value++;
                            lightController.setBrightness(curr->value);
                        }
                        else if(curr->name == str(Color)){
                            curr->value++;
                            lightController.setColor(curr->value);
                        }
                        else if(curr->name == str(ESM)){
                            curr->value = !curr->value;
                        }

                        // update the screen with the udpatedValues
                        displayController.updateValues(currSelected);

                        prev_state = state;
                        state = CHANGE_SETTING;
                    }
                    else if( bPressedID == DOWNBUTTONID){
                        if(curr->name == str(Brightness)){
                            curr->value--;
                            lightController.setBrightness(curr->value);
                        }
                        else if(curr->name == str(Color)){
                            curr->value--;
                            lightController.setColor(curr->value);
                        }
                        else if(curr->name == str(ESM)){
                            curr->value = !curr->value;
                        }
                        // update the screen with the udpatedValues
                        displayController.updateValues(currSelected);

                        prev_state = state;
                        state = CHOOSE_SETTING;
                    }
                    else if(bPressedID == CHECKBUTTONID ||
                            bPressedID == CANCELBUTTONID)
                    {
                        currSelected++;
                        prev_state = state;
                        state = CHANGE_SETTING;
                    }
                break;
                }
            }
        }
    }
};
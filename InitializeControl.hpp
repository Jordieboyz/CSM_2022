// Local Include Files
#include "res/settings.hpp"
#include "Display/displayControl.hpp"
#include "Button/buttonHandler.hpp"

class InitializeControl :   public rtos::task<>, 
                            public ButtonListener  {

public:
    void initialize() {
        startInitFlag.set();
    };

    void buttonPressed(int buttonID) {
        bPressedChannel.write(buttonID);
    };


    InitializeControl(smartLightSettings &sets,
                        DisplayControl &dispControl,
                        Button &upBut,
                        Button &downBut,
                        Button &checkBut,
                        Button &cancelBut,
                        ButtonHandler &butHandler) :

        task(2, "InitializeControl"),
        startInitFlag(this),
        bPressedChannel(this),

        settings(sets),
        displayController(dispControl),
        upButton(upBut),
        downButton(downBut),
        checkButton(checkBut),
        cancelButton(cancelBut)
    {
        butHandler.addButton(&upBut);
        butHandler.addButton(&downBut);
        butHandler.addButton(&checkBut);
        butHandler.addButton(&cancelBut);

        upButton.addButtonListener(this);
        downBut.addButtonListener(this);
        checkBut.addButtonListener(this);
        cancelBut.addButtonListener(this);
    }

private:

    enum state_t { WAIT = 0, STARTUP, CHOOSE_SETTING, CHANGE_SETTING};
    state_t state = WAIT;
    state_t prev_state = WAIT;
       
    rtos::flag startInitFlag;

    rtos::channel<int, 12> bPressedChannel;

    selectableSettings currSelected;
    screen currScreen = screen::startInitializeScreen;
    int bPressedID = -1;
    int tmpSettVal = -1;

    smartLightSettings& settings;
    DisplayControl& displayController;

    Button& upButton;
    Button& downButton;
    Button& checkButton;
    Button& cancelButton;


    void main() override {
        while(true){
            switch (state){
                case WAIT :
                {
                    wait(startInitFlag);

                    currScreen = screen::startInitializeScreen;
                    currSelected = modeSettings();

                    prev_state = state;
                    state = STARTUP;
                break;   
                }
                case STARTUP :
                {
                    if(state != prev_state)
                        displayController.showScreen(currScreen);
                    displayController.showSelector(currSelected);

                    wait(bPressedChannel);

                    bPressedID = bPressedChannel.read();

                    if( bPressedID == UPBUTTONID || bPressedID == DOWNBUTTONID){
                        currSelected = !currSelected;
                        prev_state = state;
                        state = STARTUP;
                    }
                    else if(bPressedID == CHECKBUTTONID){
                        settings.setSetting(str(Mode), currSelected);
                        if(currSelected == modes::Manual){
                            currScreen = screen::manualInitScreen;
                            currSelected = manualSettings();
                        } 
                        else if(currSelected == modes::Automatic ){
                            currScreen = screen::automaticInitScreen;
                            currSelected = automaticSettings();
                        }

                        prev_state = state;
                        state = CHOOSE_SETTING;
                    } 
                    else if(bPressedID == CANCELBUTTONID) {
                        prev_state = state;
                        state = WAIT;
                    }
                    break;
                }
                case CHOOSE_SETTING :
                {
                    // prevent writing the whole screen everytime you use the up or downbutton
                    if(prev_state != state){
                        displayController.showScreen(currScreen);
                        tmpSettVal = -1;
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
                    // have to do this because the otherscopes cant see it...
                    Setting* curr = settings.at(currSelected);

                    
                    // prevent writing the whole screen everytime you use the up or downbutton
                    if(prev_state != state){
                        // Setting* curr = settings.at(currSelected);
                        tmpSettVal = curr->value;
                        displayController.showScreen(currScreen);
                    }

                    displayController.showSelector(currSelected);

                    wait(bPressedChannel);

                    bPressedID = bPressedChannel.read();

                    if( bPressedID == UPBUTTONID ){
                        curr->value++;
                        
                        // update the screen with the udpatedValues
                        displayController.updateValues(currSelected);

                        prev_state = state;
                        state = CHANGE_SETTING;
                    }
                    else if( bPressedID == DOWNBUTTONID){
                        curr->value--;
                        
                        // update the screen with the udpatedValues
                        displayController.updateValues(currSelected);

                        prev_state = state;
                        state = CHOOSE_SETTING;
                    }
                    else if(bPressedID == CHECKBUTTONID )
                    {
                        currSelected++;

                        prev_state = state;
                        state = CHOOSE_SETTING;
                    }
                    else if(bPressedID == CANCELBUTTONID){

                        // reset the value if cancelled
                        curr->value = tmpSettVal;

                        prev_state = state;
                        state = CHOOSE_SETTING;
                    }
                break;
                }
            }
        }
    }
};
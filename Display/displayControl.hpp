
#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_

enum screen { startInitializeScreen, manualInitScreen, 
                automaticInitScreen, manualManageLightsScreen };

class Display {
public:
    void write(pos position, int rgb);
};

class DisplayControl {
private:
    Display dsp;

public:
    void showSelector(int offset) {};
    void showScreen(int screen) {};
    void updateValues(int offset = 0) {};
};

#endif /* _DISPLAY_HPP_ */
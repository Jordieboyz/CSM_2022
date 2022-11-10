#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

// Local Include Files
#include "buttonListener.hpp"


class Button {
public:
    Button(const int ID = 0) :
        ID(ID)
    {}

    void addButtonListener(ButtonListener *buttonListener) { };

    void update() { };
private:
    ButtonListener* ButtonListeners[10] = {};

    size_t curr_arr_size = 0;

    const int ID;
};

#endif /* _BUTTON_HPP_ */
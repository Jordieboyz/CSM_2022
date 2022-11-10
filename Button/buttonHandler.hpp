#ifndef _BUTTON_HANDLER_HPP_
#define _BUTTON_HANDLER_HPP_

// Local Include Files
#include "button.hpp"


class ButtonHandler : public rtos::task<> {
public:
    void addButton(Button *but){}

private:
    Button* buttons[10];

    void main() override {};
};

#endif /* _BUTTON_HANDLER_HPP_ */
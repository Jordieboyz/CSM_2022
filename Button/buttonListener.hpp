#ifndef _BUTTON_LISTENER_HPP_
#define _BUTTON_LISTENER_HPP_


class ButtonListener {
public:
    virtual void buttonPressed( int buttonID ) = 0;
};

#endif /* _BUTTON_LISTENER_HPP_ */
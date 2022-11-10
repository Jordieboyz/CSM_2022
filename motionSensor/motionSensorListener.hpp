#ifndef _MOTION_SENSOR_LISTENER_HPP_
#define _MOTION_SENSOR_LISTENER_HPP_


class motionListener {
public:
    virtual void motionIsDetected( int motionSensID ) = 0;
};

#endif /* _MOTION_SENSOR_LISTENER_HPP_ */
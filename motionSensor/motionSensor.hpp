#ifndef _MOTION_SENSOR_HPP_
#define _MOTION_SENSOR_HPP_

// Local Include Files
#include "motionSensorListener.hpp"

class MotionSensor {
public:
    MotionSensor(int ID = 0) :
        ID(ID)
    {}

    void addMotionListener(motionListener *motionListener){};

    void update(){};
private:
    motionListener* motionListeners[5] = {};

    size_t curr_arr_size = 0;
    
    const int ID = 0;    
};

#endif /* _MOTION_SENSOR_HPP_ */
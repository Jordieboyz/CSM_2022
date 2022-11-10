#ifndef _MOTION_SENSOR_HANDLER_HPP_
#define _MOTION_SENSOR_HANDLER_HPP_

// Local Include Files
#include "motionSensor.hpp"

class MotionSensorHandler : public rtos::task<> {
public:
    void addMotionSensor(MotionSensor *motionSensor){}

private:
    MotionSensor* MotionSensors[10];

    void main() override {};
};

#endif /* _MOTION_SENSOR_HANDLER_HPP_ */
#pragma once

#include <string>
#include <stdint.h>
#include "SensorTypes.h"

struct SSensorState
{
    //Info
    std::string sensorName = "";
    int8_t sensorVersion = -1;

    //Event
    int32_t timestamp = -1;
    int8_t sensorID = -1;
    eSensorType sensorType = eSensorType::I2C;

    union
    {
        float data[4];
        float temperatureCelsius[4];
    };
};
#pragma once

#include <memory>
#include "SensorState.h"


class CAbstractSensor
{
protected:    
    int m_UniqueID = -1;
    SSensorState m_SensorState;

public:
    CAbstractSensor(int uniqueID)
        :   m_UniqueID(uniqueID)
    {
        
        m_SensorState.sensorID = uniqueID;
        m_SensorState.sensorName = "Abstract";
        //m_SensorState.sensorName = "Abstract";
        m_SensorState.sensorType = eSensorType::NONE;
        m_SensorState.sensorVersion = -1.0;
    }

    const SSensorState& getState() const
    {
        return m_SensorState;
    }

    int getUid() const
    {
        return m_UniqueID;
    }

    virtual void update() = 0;
};
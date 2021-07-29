#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "AbsSensor.h"
#include "SensorState.h"


namespace std
{
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};

class CNodeSensors
{
private:
    SSensorState m_DummyState; // Null State that is returned when no available sensor is found;
    std::vector<std::unique_ptr<CAbstractSensor>> m_Sensors;
public:
    CNodeSensors()
    {
        m_DummyState.sensorName = "None";
    }

    template<typename T, typename ...TParams>
    void attach(TParams&&... params)
    {
        static_assert(std::is_convertible<T*, CAbstractSensor*>::value, "Type T must inherit CAbstractSensor as public");

        //Construct type T object from parameters
        auto newSensor = std::make_unique<T>(std::forward<TParams>(params)...);
        m_Sensors.emplace_back(std::move(newSensor));
    }

    const SSensorState& readSensor(int uniqueID)
    {
        auto found = std::find_if(m_Sensors.begin(), m_Sensors.end(), [uniqueID](const std::unique_ptr<CAbstractSensor>& sensor){
            return sensor->getUid() == uniqueID;
        });

        if(found != m_Sensors.end())
        {//Found
            return (*found)->getState();
        }
        else
        {//Not found
            return m_DummyState;
        }
    }

    void update()
    {
        for(const auto& sensor: m_Sensors)
        {
            sensor->update();
        }        
    }
};
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
    CNodeSensors();

    size_t size() const;

    template<typename T, typename ...TParams>
    void attach(TParams&&... params);

    const SSensorState& readSensor(int uniqueID);

    void update();
};

//Template needs to be defined in .h - Otherwise compiler is unable to see it
template<typename T, typename ...TParams>
void CNodeSensors::attach(TParams&&... params)
{
    static_assert(std::is_convertible<T*, CAbstractSensor*>::value, "Type T must inherit CAbstractSensor as public");

    //Construct type T object from parameters
    auto newSensor = std::make_unique<T>(std::forward<TParams>(params)...);
    m_Sensors.emplace_back(std::move(newSensor));
}
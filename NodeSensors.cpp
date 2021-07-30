#include "NodeSensors.h"

CNodeSensors::CNodeSensors()
{
    m_DummyState.sensorName = "None";
}

size_t CNodeSensors::size() const
{
    return m_Sensors.size();
}


const SSensorState& CNodeSensors::readSensor(int uniqueID)
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

void CNodeSensors::update()
{
    for(const auto& sensor: m_Sensors)
    {
        sensor->update();
    }        
}
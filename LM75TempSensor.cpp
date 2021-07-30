
#include "LM75TempSensor.h"

CLM75TemperatureSensor::CLM75TemperatureSensor(int uniqueID, TwoWire* twoWire, int i2cAddress)
    :   CAbstractSensor(uniqueID),
        m_I2C(twoWire),
        m_Thermo(m_I2C, i2cAddress)
{
    //TwoWrite Must be already started. (.begin() called)
    //m_I2C.begin(twoWireAddress.SDA, twoWireAddress.SCL, twoWireAddress.frequency);
    
    m_SensorState.sensorName = "LM75";
    m_SensorState.sensorType = TYPE;
    m_SensorState.sensorVersion = 1.0;
}

CLM75TemperatureSensor::~CLM75TemperatureSensor()
{
}

void CLM75TemperatureSensor::update()
{   
    
    float val = m_Thermo.readTemperatureC();

    m_SensorState.timestamp = millis();
    m_SensorState.temperatureCelsius[0] = val;
    m_SensorState.temperatureCelsius[1] = 0;
    m_SensorState.temperatureCelsius[2] = 0;
    m_SensorState.temperatureCelsius[3] = 0;
}
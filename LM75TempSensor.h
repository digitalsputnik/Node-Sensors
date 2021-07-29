#pragma once

#include <memory>
#include <time.h>


#include <Wire.h>
#include <Temperature_LM75_Derived.h>

#include "SensorTypes.h"
#include "AbsSensor.h"

struct STwoWireAddress
{
    int SDA = 4;
    int SCL = 21;
    int speed = 100000;
    int i2cAddress = 0x49;    

    STwoWireAddress(int sda, int scl, int speed, int i2cA): SDA(sda), SCL(scl), speed(speed), i2cAddress(i2cA){}    
};

class CLM75TemperatureSensor: public CAbstractSensor
{
public:
static constexpr eSensorType TYPE = eSensorType::I2C;

private:
    TwoWire m_I2CTemp; // Need to scan if 1 or 2
    Generic_LM75* m_Thermo; // Owned pointer, deleted on object destruction
public:
    CLM75TemperatureSensor(int uniqueID, STwoWireAddress twoWireAddress)
        :   CAbstractSensor(uniqueID),
            m_I2CTemp(1)
    {
        m_I2CTemp.begin(twoWireAddress.SDA, twoWireAddress.SCL, twoWireAddress.speed);
        m_Thermo = new Generic_LM75(&m_I2CTemp, twoWireAddress.i2cAddress);
        
        m_SensorState.sensorName = "LM75";
        m_SensorState.sensorType = TYPE;
        m_SensorState.sensorVersion = 1.0;
    }

    ~CLM75TemperatureSensor()
    {
        delete m_Thermo;
    }

    virtual void update() override
    {   
        
        float val = m_Thermo->readTemperatureC();

        m_SensorState.timestamp = millis();
        m_SensorState.temperatureCensius[0] = val;
        m_SensorState.temperatureCensius[1] = 0;
        m_SensorState.temperatureCensius[2] = 0;
        m_SensorState.temperatureCensius[3] = 0;
    }
};
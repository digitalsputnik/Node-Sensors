#pragma once
#include <memory>
#include <time.h>

#include <Wire.h>
#include <Temperature_LM75_Derived.h>

#include "SensorTypes.h"
#include "AbsSensor.h"

class CLM75TemperatureSensor: public CAbstractSensor
{
public:
static constexpr eSensorType TYPE = eSensorType::I2C;

private:
    TwoWire* m_I2C = nullptr; // Non owning pointer to TwoWire instance
    Generic_LM75 m_Thermo;
public:
    CLM75TemperatureSensor(int uniqueID, TwoWire* twoWire, int i2cAddress);

    virtual ~CLM75TemperatureSensor();

    virtual void update() override;
};

#include "LM75TempSensor.cpp" // TODO: Remove on commit

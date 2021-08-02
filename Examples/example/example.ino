#include <Arduino.h>

#include <NodeSensors.h>
#include <LM75TempSensor.h>

enum EI2CAddresses
{
    LM75 = 0x49
};

namespace HardwareConfig
{
    constexpr int I2C_SDA = 4;
    constexpr int I2C_SCL = 21;
    constexpr int I2C_FREQUENCY = 100000;
};

CNodeSensors sensors;

// Twowire outside of NodeSensor interface, allows to create multiple sensors connected to same wire.
// 
// Sensor interfaces(TwoWire) can be hidden inside derived NodeSensors.
// This derived NodeSensor would provide all interfaces present for any given hardware device. 
// also allowing user to create custom sensor configuration for any hardware
TwoWire i2c(1); 

void setup()
{
    Serial.begin(115200);
    i2c.begin(HardwareConfig::I2C_SDA, HardwareConfig::I2C_SCL, HardwareConfig::I2C_FREQUENCY);

    sensors.attach<CLM75TemperatureSensor>(0, &i2c, EI2CAddresses::LM75);
}

static const uint64_t REFRESH_INTERVAL = 1000; // ms
static uint64_t lastRefreshTime = 0;
void loop()
{
    auto start = millis();
    if(start - lastRefreshTime >= REFRESH_INTERVAL)
    {
        Serial.println("Updating sensors");

        sensors.update(); // Update all sensors

        Serial.printf("Sensors updated in: %ims\n", (millis() - start));

        {
            int i = 0;
            const auto& readState = sensors.readSensor(i); // Read state of sensor with id 0
            //Display sensor state, interpreted as temperatureCelsius
            Serial.printf("Sensor(%i) '%s' state: %f, %f, %f, %f @ %i\n", i, readState.sensorName.c_str(), readState.temperatureCelsius[0], readState.temperatureCelsius[1], readState.temperatureCelsius[2], readState.temperatureCelsius[3], readState.timestamp);
        }

        lastRefreshTime += REFRESH_INTERVAL;
    }
}

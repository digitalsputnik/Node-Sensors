#include <Arduino.h>
#include <Wire.h>
#include <memory>

#include "../LM75TempSensor.h"
#include "../SensorTypes.h"
#include "../NodeSensors.h"

CNodeSensors sensors;

void setup()
{
    Serial.begin(115200);
    Serial.println("Hello LM75Test");

    //Create LM75 temperature sensor with ID 0 at address SDA: 4, SCL: 21, i2c address 0x49
    sensors.attach<CLM75TemperatureSensor>(0, STwoWireAddress{4, 21, 100000, 0x49});
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

        const auto& readState = sensors.readSensor(0); // Read state of sensor with id 0

        //Display sensor state, interpreted as temperatureCelsius
        Serial.printf("Sensor '%s' state: %f, %f, %f, %f @ %i\n", readState.sensorName.c_str(), readState.temperatureCelsius[0], readState.temperatureCelsius[1], readState.temperatureCelsius[2], readState.temperatureCelsius[3], readState.timestamp);

        lastRefreshTime += REFRESH_INTERVAL;
    }
}

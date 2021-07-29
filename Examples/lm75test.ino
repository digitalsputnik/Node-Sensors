#include <Arduino.h>
#include <Wire.h>
#include <memory>

#include "../LM75TempSensor.h"
#include "../SensorTypes.h"
#include "../NodeSensors.h"

//CSensorManager sensors;
//sensors.attach<CLM75TemperatureSensor>(STwoWireAddress);
//sensors.


CNodeSensors sensors;

void setup()
{
    Serial.begin(115200);
    Serial.println("Hello LM75Test");

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

        sensors.update();

        Serial.printf("Sensors updated in: %ims\n", (millis() - start));

        auto readState = sensors.readSensor(0); // User must know how to interpret given unique ID. What Union member has proper data.
        //Idea: Create compile time generated Unique ID that is accessible via CLM75Sensor::uniqueID - Type is 100% clear what user wants to access.
        //With given interface, sensorState can always be interpreter correctly according to type. Interpretation layer can be added via CLM75Sensor::Interpret(sensorState) -> Float[4]&
        //Currently use must access proper Union from and integer value. When Union and other sensor types are added.
        //What if multiple same type sensors ?


        Serial.printf("Sensor '%s' state: %f, %f, %f, %f @ %i\n", readState.sensorName.c_str(), readState.temperatureCensius[0], readState.temperatureCensius[1], readState.temperatureCensius[2], readState.temperatureCensius[3], readState.timestamp);

        lastRefreshTime += REFRESH_INTERVAL;
    }
}

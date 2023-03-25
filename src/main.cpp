#include <Arduino.h>
#include "displayDriver.h"
#include "wifiDriver.h"
#include "restDriver.h"

void setup()
{
    Serial.begin(115200);
    for (size_t i = 5; i > 0; i--)
    {
        Serial.printf("Starting in %d\n", i);
        delay(1000);
    }
    
    displayDriver displayDriver;
    wifiDriver wifiDriver;
    restDriver restDriver(wifiDriver, displayDriver);

    std::string database = restDriver.GETRequest();

    String data = "{\"Box1\":1}";
    Serial.printf("sending %s, with length %d\n", data, sizeof(data));

    restDriver.PUTRequest(data);

    database = restDriver.GETRequest();
    // displayDriver.LOG(database);
}

void loop()
{
    delay(1000);
}
#include "restDriver.h"


WiFiClientSecure restDriver::StartWifiClient(void)
{
    WiFiClientSecure client;
    client.setInsecure();
    return client;
}

void restDriver::timerOk(void)
{
    while ((millis() - timer) < restLimit);
}

void restDriver::setTimer(void)
{
    timer = millis();
}

bool restDriver::GETRequest(String &data)
{
    wifi->wifiConnect();
    HTTPClient http;
    WiFiClientSecure client = StartWifiClient();
    http.begin(client, baseUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-apikey", apiKey);

    timerOk();
    int httpResponseCode = http.GET();
    setTimer();
    data = http.getString();

    http.end();    
    wifi->wifiDisconnect();

    if (httpResponseCode == 200)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool restDriver::PUTRequest(String payload)
{
    wifi->wifiConnect();
    HTTPClient http;
    WiFiClientSecure client = StartWifiClient();
    String url = baseUrl + "/" + databaseID;
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-apikey", apiKey);
    http.addHeader("cache-control", "no-cache");

    timerOk();
    int httpResponseCode = http.PUT(payload);
    setTimer();
    String response = http.getString();

    http.end();    
    wifi->wifiDisconnect();

    if (httpResponseCode == 200)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int restDriver::findValueFromPayload(std::string retrievedPayload, int box, int &value)
{
    char boxChar = box + '0';
    char temp[5] = "Box";
    temp[3] = boxChar;
    temp[4] = '\0';
    int pos = retrievedPayload.find(temp);
    value = retrievedPayload[pos+6] - '0';
    if (value >= 0)
    {
        return true;
    }
    else
    {
        Serial.println("Retrying PUT...");
        return false;
    }
}

String restDriver::createPutPayload(int box, int value)
{
    String boxStr = (String) box;
    String valueStr = (String) value;
    String data = "{\"Box" + boxStr + "\":" + valueStr + "}";
    return data;
}

restDriver::restDriver(wifiDriver &wifidriver)
{
    wifi = &wifidriver;
}

bool restDriver::updateBoxValue(int box, int value)
{
    String data = createPutPayload(box, value);
    return PUTRequest(data);
}

int restDriver::retrieveBoxValue(int box)
{
    String databaseData;
    int value = 0;
    do
    {
        GETRequest(databaseData);
    } while (!findValueFromPayload(databaseData.c_str(), box, value));
    return value;
}
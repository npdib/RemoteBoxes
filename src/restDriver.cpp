#include "restDriver.h"


WiFiClientSecure restDriver::StartWifiClient(void)
{
    WiFiClientSecure client;
    client.setInsecure();
    return client;
}

std::string restDriver::GETRequest(void)
{
    wifi.wifiConnect();
    HTTPClient http;
    WiFiClientSecure client = StartWifiClient();
    http.begin(client, baseUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-apikey", apiKey);

    int httpResponseCode = http.GET();
    std::string response = http.getString().c_str();

    http.end();    
    wifi.wifiDisconnect();
    display.LOG(response);

    return response;
}

bool restDriver::PUTRequest(uint8_t* payload, size_t size)
{
    wifi.wifiConnect();
    HTTPClient http;
    WiFiClientSecure client = StartWifiClient();
    String url = baseUrl + "/" + databaseID;
    display.LOG(url.c_str());
    Serial.print((char*) payload);
    http.begin(client, baseUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-apikey", apiKey);

    int httpResponseCode = http.PUT(payload, size);
    std::string response = http.getString().c_str();
    Serial.printf("response code %d; response %s", httpResponseCode, response.c_str());

    http.end();    
    wifi.wifiDisconnect();

    if (httpResponseCode == 200)
    {
        return true;
    }
    else
    {
        return false;
    }
}

restDriver::restDriver(wifiDriver wifidriver, displayDriver displaydriver)
{
    wifi = wifidriver;
    display = displaydriver;
}
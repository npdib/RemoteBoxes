#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "wifiDriver.h"
#include "displayDriver.h"

class restDriver
{
    private:    
        String baseUrl = "https://o9mcwkem39.execute-api.eu-north-1.amazonaws.com/items";
        String databaseID = "NickAndKatieBox";

        wifiDriver* wifi;
        
        WiFiClientSecure StartWifiClient(void);

        bool GETRequest(String &);
        bool PUTRequest(String);
        int findValueFromPayload(std::string, int, int &);
        String createPutPayload(int, int);  

    public:
        restDriver(wifiDriver &); // constructor
        bool updateBoxValue(int, int);
        int retrieveBoxValue(int);
};
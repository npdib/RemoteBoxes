#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "wifiDriver.h"
#include "displayDriver.h"

class restDriver
{
    private:    
        String baseUrl = "https://katiebox1-05ba.restdb.io/rest/nkboxes";
        String databaseID = "640e11dee603b60500012346";
        String apiKey = "640e0c86bc22d22cf7b25e75";

        wifiDriver wifi;
        displayDriver display;
        
        WiFiClientSecure StartWifiClient(void);
        

    public:
        restDriver(wifiDriver, displayDriver); // constructor
        std::string GETRequest(void);
        bool PUTRequest(uint8_t*, size_t);
};
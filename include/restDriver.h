#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "wifiDriver.h"
#include "displayDriver.h"

class restDriver
{
    private:    
        String baseUrl = "https://katiebox1-05ba.restdb.io/rest/nkboxes";
        String databaseID = "641f2aba111de45d00014b37";
        String apiKey = "640e0c86bc22d22cf7b25e75";

        wifiDriver wifi;
        displayDriver display;
        
        WiFiClientSecure StartWifiClient(void);
        

    public:
        restDriver(wifiDriver, displayDriver); // constructor
        std::string GETRequest(void);
        bool PUTRequest(String);
};
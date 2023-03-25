#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "wifiDriver.h"
#include "displayDriver.h"

constexpr int restLimit = 1020;

class restDriver
{
    private:    
        String baseUrl = "https://katiebox1-05ba.restdb.io/rest/nkboxes";
        String databaseID = "641f4634111de45d00015467";
        String apiKey = "640e0c86bc22d22cf7b25e75";

        int timer = 0;

        wifiDriver* wifi;
        
        WiFiClientSecure StartWifiClient(void);

        void timerOk(void);
        void setTimer(void);

        bool GETRequest(String &);
        bool PUTRequest(String);
        int findValueFromPayload(std::string, int, int &);
        String createPutPayload(int, int);  

    public:
        restDriver(wifiDriver &); // constructor
        bool updateBoxValue(int, int);
        int retrieveBoxValue(int);
};
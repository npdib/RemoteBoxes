#ifndef WIFIDRIVER
#define WIFIDRIVER

#include <WiFi.h>
#include "SDDriver.h"

class wifiDriver
{
    private:
        WiFiCredentials mCredentials;
        WiFiCredentials getSSIDfromFile(void);

    public:
        wifiDriver(void); // constructor
        void wifiConnect(void);
        void wifiDisconnect(void) {WiFi.disconnect(false, false);}
};

#endif //WIFIDRIVER
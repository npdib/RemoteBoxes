#ifndef WIFIDRIVER
#define WIFIDRIVER

#include <WiFi.h>

class wifiDriver
{
    private:
        std::string mCredentials = "";
        std::string mSSID = "";
        std::string mPwd = "";
        std::string getSSIDfromFile(void);

    public:
        wifiDriver(void); // constructor
        void wifiConnect(void);
        void wifiDisconnect(void) {WiFi.disconnect(false, false);}
};

#endif //WIFIDRIVER
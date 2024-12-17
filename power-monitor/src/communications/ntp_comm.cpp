#include "config.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ntpServerName = "north-america.pool.ntp.org";
int secUpdateInterval = 60;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServerName, Config::GMT_TIME_ZONE * 3600, secUpdateInterval);

void SynchronizeDateTime() {
    timeClient.update();
}
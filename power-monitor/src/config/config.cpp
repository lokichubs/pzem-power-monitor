#include "config.h"
#include <Arduino.h>

// Define configuration parameters needed for the SoC
namespace Config
{
    const char* WIFI_SSID = "ASUS_IOT";
    const char* WIFI_PASSWORD = "ASUS_IOT";
    const char* MQTT_SERVER_IP = "172.24.1.138";
    const int MQTT_SERVER_PORT = 1883;
    const int SERIAL_BAUD_RATE = 115200;
    const int LOOP_INTERVAL_MSEC = 2000;
    const int GMT_TIME_ZONE = -5;
    const int NUMBER_OF_PZEMS = 1;
    const int PZEM_RX_PIN = 16;
    const int PZEM_TX_PIN = 17;
    const int STARTING_COMM_ID = 0x10;
}

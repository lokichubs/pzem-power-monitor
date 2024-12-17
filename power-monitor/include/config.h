#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

namespace Config
{
    extern const char* WIFI_SSID;    
    extern const char* WIFI_PASSWORD;	
    extern const char* MQTT_SERVER_IP;
    extern const int MQTT_SERVER_PORT;			
    extern const int SERIAL_BAUD_RATE;
    extern const int LOOP_INTERVAL_MSEC;
    extern const uint8_t AIR_QUALITY_PIN;
    extern const uint8_t PROXIMITY_PIN;
    extern const uint8_t ACOUSTIC_PIN;
    extern const uint8_t DHT_PIN;
    extern const int GMT_TIME_ZONE;
    extern const int NUMBER_OF_PZEMS;
    extern const int PZEM_RX_PIN;
    extern const int PZEM_TX_PIN;
    extern const int STARTING_COMM_ID;
}

#endif
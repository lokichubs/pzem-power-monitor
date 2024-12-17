#ifndef WIFI_COMM_H
#define WIFI_COMM_H
#include <WiFi.h>
#include <Arduino.h>

bool EstablishWiFiCommunication();
String _wLStatusToString(wl_status_t status);
String ObtainMACAddressString();

#endif
#include "wifi_comm.h"
#include "serial_comm.h"
#include "config.h"
#include <WiFi.h>
#include <ESPmDNS.h>

static int maxConnectionAttempts = 3;
static int msecBetweenAttempts = 1000;

bool EstablishWiFiCommunication() {
    // Specify connection parameters
    LogDebugData(String("MAC Address: " + WiFi.macAddress()).c_str());
    WiFi.setHostname(ObtainMACAddressString().c_str());
    WiFi.setSleep(false);
    WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);

    // Attempt to create connection
    int connectionAttempts = 0;
    bool isConnected = (WiFi.status() == WL_CONNECTED);
    LogDebugData(String("WiFi Connection Status: " + _wLStatusToString(WiFi.status())).c_str());
    while ((!isConnected) && (connectionAttempts < maxConnectionAttempts)) {
        delay(msecBetweenAttempts);
        isConnected = (WiFi.status() == WL_CONNECTED);
        LogDebugData(String("WiFi Connection Status: " + _wLStatusToString(WiFi.status())).c_str());
        connectionAttempts += 1;
    }

    if (isConnected) {
        LogDebugData(String("Network SSID: " + WiFi.SSID()).c_str());
        LogDebugData(String("IP Address: " + WiFi.localIP().toString()).c_str());
        LogDebugData(String("Gateway: " + WiFi.gatewayIP().toString()).c_str());
    }
    return isConnected;
}

String _wLStatusToString(wl_status_t status) {
    switch (status) {
        case WL_NO_SHIELD: return "WL_NO_SHIELD";
        case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
        case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
        case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
        case WL_CONNECTED: return "WL_CONNECTED";
        case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
        case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
        case WL_DISCONNECTED: return "WL_DISCONNECTED";
        default: return "";
    }
}

String ObtainMACAddressString() {
    String macAddress = WiFi.macAddress();
    macAddress.replace(":","");
    return macAddress;
}
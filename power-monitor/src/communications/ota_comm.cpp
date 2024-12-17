#include "ota_comm.h"
#include "serial_comm.h"
#include "wifi_comm.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <Update.h>

AsyncWebServer server(80);
size_t content_len;
static int maxConnectionAttempts = 3;
static int msecBetweenAttempts = 250;

void _handleUpdate(AsyncWebServerRequest* request)
{
    request->send(200, "text/html", serverIndex.c_str());
}

void _handleDoUpdate(AsyncWebServerRequest* request, const String& filename, size_t index, uint8_t* data, size_t len, bool final)
{
    if (!index) {
        LogDebugData("Received request to update code");
        content_len = request->contentLength();

        // If filename includes spiffs, update the spiffs partition
        int cmd = (filename.indexOf("spiffs") > -1) ? U_SPIFFS : U_FLASH;
        if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd)) {
            Update.printError(Serial);
        }
    }

    if (Update.write(data, len) != len) {
        Update.printError(Serial);
    }

    if (final) {
        AsyncWebServerResponse* response = request->beginResponse(302, "text/plain", "Please wait while the device reboots");
        response->addHeader("Refresh", "0");
        response->addHeader("Location", "/");
        request->send(response);
        if (!Update.end(true)) {
            Update.printError(Serial);
        }
        else {
            LogDebugData("OTA update completed");
            Serial.flush();
            ESP.restart();
        }
    }
}

void EstablishOTAServer() {
    LogDebugData("OTA Server launched");
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {request->redirect("/update"); });
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) { _handleUpdate(request); });
    server.on("/doUpdate", HTTP_POST,
        [](AsyncWebServerRequest* request) {},
        [](AsyncWebServerRequest* request, const String& filename, size_t index, uint8_t* data,
            size_t len, bool final) { _handleDoUpdate(request, filename, index, data, len, final); }
    );
    server.onNotFound([](AsyncWebServerRequest* request) {request->send(404); });
    server.begin();
}

bool EstablishMDNSResponder() {
    // Specify MDNS parameters and attempt to establish Responder
    int connectionAttempts = 0;
    bool isConnected = RestartMDNSResponder();
    while((!isConnected) && (connectionAttempts < maxConnectionAttempts))
    {
        delay(msecBetweenAttempts);
        isConnected = RestartMDNSResponder();
        connectionAttempts += 1;
    }

    if (isConnected) {
        MDNS.addService("_http", "_tcp", 80);
        LogDebugData("MDNS successfully established");
    }

    return isConnected;
}

bool RestartMDNSResponder() {
    bool isStarted = MDNS.begin(ObtainMACAddressString().c_str());
    LogDebugData("MDNS Responder restarted");
    return isStarted;
}
#include "serial_comm.h"
#include "config.h"
#include <Arduino.h>

static int maxConnectionAttempts = 3;
static int msecBetweenAttempts = 250;

void EstablishSerialCommunication() {
    // Specify connection parameters
    Serial.begin(Config::SERIAL_BAUD_RATE);
    int connectionAttempts = 0;

    while ((!Serial) && (connectionAttempts < maxConnectionAttempts)) {
        delay(msecBetweenAttempts);
        connectionAttempts += 1;
    }

    if(!Serial) {
        // If the serial port is not available, restart the device and try again
        ESP.restart();
    }

    Serial.println();
    LogDebugData("Serial channel ready");
}

void LogDebugData(String debugData) {
    Serial.print("[DEBUG],");
    Serial.println(debugData);
}

void LogSensorData(String sensorName, String sensorData, String sensorUnits) {
    Serial.print("[DATA],");
    Serial.print(sensorName);
    Serial.print(",");
    Serial.print(sensorData);
    Serial.print(",");
    Serial.println(sensorUnits);
}
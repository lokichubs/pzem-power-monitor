#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H
#include <Arduino.h>

void EstablishSerialCommunication();
void LogDebugData(String debugData);
void LogSensorData(String sensorName, String sensorData, String sensorUnits);

#endif
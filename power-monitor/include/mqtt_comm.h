#ifndef MQTT_COMM_H
#define MQTT_COMM_H
#include <Arduino.h>

bool EstablishMQTTConnection();
String PubSubStateToString(int state);
void RecordData(String dataName, String payloadData, String payloadUnits, bool isMQTTConnected);
void PublishData(String topicName, String topicPayload);

#endif
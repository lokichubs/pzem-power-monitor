#include "mqtt_comm.h"
#include "wifi_comm.h"
#include "serial_comm.h"
#include "config.h"
#include <WiFi.h>
#include <PubSubClient.h>

static WiFiClient espClient;
static PubSubClient client(espClient);;
static int maxConnectionAttempts = 3;
static int msecBetweenAttempts = 500;

bool EstablishMQTTConnection() {
    // Specify connection parameters
    client.setServer(Config::MQTT_SERVER_IP, Config::MQTT_SERVER_PORT);
    client.setSocketTimeout(msecBetweenAttempts);

    // Attempt to create connection
    int connectionAttempts = 0;
	bool isConnecting = client.connect(ObtainMACAddressString().c_str());
    while((!isConnecting) && (connectionAttempts < maxConnectionAttempts)) {
        isConnecting = client.connect(ObtainMACAddressString().c_str());
        connectionAttempts += 1;
    }

    bool isConnected = client.connected();
    LogDebugData(String("MQTT Connection Status: " + PubSubStateToString(client.state())).c_str());
    return isConnected;
}

String PubSubStateToString(int state) {
    switch (state) {
        case -4: return "MQTT_CONNECTION_TIMEOUT";
        case -3: return "MQTT_CONNECTION_LOST";
        case -2: return "MQTT_CONNECT_FAILED";
        case -1: return "MQTT_DISCONNECTED";
        case 0: return "MQTT_CONNECTED";
        case 1: return "MQTT_CONNECT_BAD_PROTOCOL";
        case 2: return "MQTT_CONNECT_BAD_CLIENT_ID";
        case 3: return "MQTT_CONNECT_UNAVAILABLE";
        case 4: return "MQTT_CONNECT_BAD_CREDENTIALS";
        case 5: return "MQTT_CONNECT_UNAUTHORIZED";
        default: return "";
    }
}

void RecordData(String dataName, String payloadData, String payloadUnits, bool isMQTTConnected) {
    LogSensorData(dataName, payloadData, payloadUnits); 
    if(isMQTTConnected) { PublishData(String(dataName + "," + payloadUnits), payloadData); }
}

void PublishData(String topicName, String topicPayload) {
    bool isPublishSuccessful = client.publish(String(ObtainMACAddressString() + "/" + topicName).c_str(), topicPayload.c_str());

    if (!isPublishSuccessful) {
        LogDebugData("Publishing unsuccessful, trying agin");
        delay(msecBetweenAttempts);
        isPublishSuccessful = client.publish(String(ObtainMACAddressString() + "/" + topicName).c_str(), topicPayload.c_str());
    }

    if(!isPublishSuccessful) { LogDebugData("Publishing failed"); }
}
#include "config.h"
#include "serial_comm.h"
#include "mqtt_comm.h"
#include "pzem_sensor.h"
#include <PZEM004Tv30.h>

#define PZEM_SERIAL Serial2

// Update this array size to match the Config::NUMBER_OF_PZEMS
PZEM004Tv30 pzems[1];

void InitializePzemSensors(){
    // Initialize each pzem with its unique ID over the Serial channel
    for(int i = 0; i < Config::NUMBER_OF_PZEMS; i++)
    {
        pzems[i] = PZEM004Tv30(PZEM_SERIAL, Config::PZEM_RX_PIN, Config::PZEM_TX_PIN, Config::STARTING_COMM_ID + i);
    }
}

void ReadPzemSensorData(bool isMQTTConnected){
    // Print out the measured values from each PZEM module
    for(int i = 0; i < Config::NUMBER_OF_PZEMS; i++)
    {
        // Print the Address of the PZEM
        LogDebugData("PZEM " + String(i) + " - Address:" + String(pzems[i].getAddress()));

        // Read the data from the sensor
        float voltage = pzems[i].voltage();
        float current = pzems[i].current();
        float power = pzems[i].power();
        float energy = pzems[i].energy();
        float frequency = pzems[i].frequency();
        float pf = pzems[i].pf();

        String dataName = "PZEM " + String(i) + " Voltage";
        String payloadData = String(voltage);
        String payloadUnits = "(V)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

        dataName = "PZEM " + String(i) + " Current";
        payloadData = String(current);
        payloadUnits = "(A)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

        dataName = "PZEM " + String(i) + " Power";
        payloadData = String(power);
        payloadUnits = "(W)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

        dataName = "PZEM " + String(i) + " Energy";
        payloadData = String(energy);
        payloadUnits = "(kWh)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

        dataName = "PZEM " + String(i) + " Frequency";
        payloadData = String(frequency);
        payloadUnits = "(Hz)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

        dataName = "PZEM " + String(i) + " PF";
        payloadData = String(pf);
        payloadUnits = "(-)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);
    }
}
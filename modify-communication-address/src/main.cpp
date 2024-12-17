#include <Arduino.h>
#include <PZEM004Tv30.h>

#define SET_ADDRESS 0x10
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#define PZEM_SERIAL Serial2

PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

void setup() {
  Serial.begin(115200);
}

void loop() {
  static uint8_t addr = SET_ADDRESS;

  Serial.print("Previous address:   0x");
  Serial.println(pzem.readAddress(), HEX);

  Serial.print("Setting address to: 0x");
  Serial.println(addr, HEX);
  if(!pzem.setAddress(addr))
  {
    Serial.println("Error setting address.");
  } else {
    Serial.print("Current address:    0x");
    Serial.println(pzem.readAddress(), HEX);
    Serial.println();
  }

  Serial.println("If the address has successfully been updated, please disconnect the pzem");
  delay(5000);
}
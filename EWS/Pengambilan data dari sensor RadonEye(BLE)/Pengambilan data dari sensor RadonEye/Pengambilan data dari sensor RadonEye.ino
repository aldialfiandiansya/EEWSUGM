/*
LoRa       ESP32
D1    <->   D27    
D0    <->   D26
SCK   <->   D18
MISO  <->   D19
MOSI  <->   D23
CS    <->   D5
RST   <->   D34

*/


#include "deklarasi.h"

// Pilih pin RX dan TX yang sesuai pada ESP32
const int rxPin = 18; // Pin RX yang digunakan
const int txPin = 19; // Pin TX yang digunakan


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, rxPin, txPin);
  Serial.println("Starting the program");
  bleClient();
  Serial.println("BLE client void setup aktif");
  esp_task_wdt_add(NULL); //add current thread to WDT watch
}

void loop() {
  esp_task_wdt_reset();
  if (millis() - previousMillis > interval) {
    esp_task_wdt_reset();
    /**************************** [ set previousTime as millis ] ****************************/
    previousMillis = millis();
    /**************************** [ connect to sensor via ble ] *****************************/
    esp_task_wdt_reset();
    if (doConnect == true) {
      if (connectToServer()) {
        Serial.println("connected to the Ble Server or Sensor");
        esp_task_wdt_reset();
      }
      else {
        Serial.println("gagal connect to ble server");
        ESP.restart();
      }
      doConnect = false;
    }
    esp_task_wdt_reset();
    /******************************* [ get data from sensor ] *******************************/
    esp_task_wdt_reset();
    if (connected == true) {
      esp_task_wdt_reset();
      Serial.println("get data");
      esp_task_wdt_reset();
      getData();
      esp_task_wdt_reset();
    }
    else {
      Serial.println("gagal get data");
      ESP.restart();
    }
    /******************************* [ check send data event ] ******************************/
    esp_task_wdt_reset();
    // analog();
    if (sendNow == true) {
      sendSerial();
      esp_task_wdt_reset();
    }
  }
}

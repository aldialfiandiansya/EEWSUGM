#include "deklarasi.h"
// Pilih pin RX dan TX yang sesuai pada ESP32
const int rxPin = 18; // Pin RX yang digunakan
const int txPin = 19; // Pin TX yang digunakan

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, rxPin, txPin);
  Serial.println("Starting the program");
  initwifiConnect();
  Serial.println("WIFI aktif");
  pingGoogle();
  Serial.println("PING berhasil");
  esp_task_wdt_add(NULL); //add current thread to WDT watch
  esp_task_wdt_reset();
//  initLoRa();
}

void loop() {
  esp_task_wdt_reset();
  if (Serial2.available()) {
    parseData();
  }
  if (millis() - previousMillis > interval) {
    esp_task_wdt_reset();
    /**************************** [ set previousTime as millis ] ****************************/
    previousMillis = millis();
    /********************************* [ check connection ] *********************************/
    if (WiFi.status() == WL_CONNECTED) {
      esp_task_wdt_reset();
      /********************************** [ try connection WIFI ] **********************************/
      pingGoogle();
      esp_task_wdt_reset();
      sendNow = true;//**************
      esp_task_wdt_reset();
      /******************************* [ check send data HTTP event ] ******************************/
      if (sendNow) {
        esp_task_wdt_reset();
        sendDataHTTP();
        sendNow = false;
      }
    }
    else {
      Serial.println("access point wifi disconnect");
      initwifiConnect();
    }
    /******************************* [ check send data LoRa event ] ******************************/
//    sendLora();
  }
}

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


void setup() {
  Serial.begin(115200);
  Serial.println("Starting the program");
  bleClient();
  Serial.println("BLE client void setup aktif");
  esp_task_wdt_add(NULL); //add current thread to WDT watch
  esp_task_wdt_reset();
  initLoRa();
  Serial.println("LoRa berhasil");
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
    if (sendNow == true) {
      int Rad = radonValue; // Contoh variabel angka
      Serial.println(Rad);
    }
    esp_task_wdt_reset();
    sendLora();
    lora.update();
    recvStatus=lora.readData(outStr);
    if (recvStatus) {
    int counter = 0;
    esp_task_wdt_reset();
    for (int i = 0; i < recvStatus; i++)
    {
      if (((outStr[i] >= 32) && (outStr[i] <= 126)) || (outStr[i] == 10) || (outStr[i] == 13))
        counter++;
    }
    if (counter == recvStatus)
    {
      Serial.print(F("Received String : "));
      for (int i = 0; i < recvStatus; i++)
      {
        Serial.print(char(outStr[i]));
      }
    }
    else
    {
      Serial.print(F("Received Hex : "));
      for (int i = 0; i < recvStatus; i++)
      {
        Serial.print(outStr[i], HEX); Serial.print(" ");
      }
    }
    Serial.println();
    }
  }
}

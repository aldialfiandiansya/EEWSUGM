#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <esp_task_wdt.h>
#include <HardwareSerial.h>
//#include <lorawan.h>
#define WDT_TIMEOUT 8

HTTPClient http;

//Wifi Info
#define ssid "CorpU_Net" //Nama Koneksi WiFi yang dipakai
#define password "corpu2022" //Password Wifi

static String receivedData = ""; // Variabel untuk menyimpan data yang diterima

//Sibolga HTTP
const char* http_server = "http://publish-data.telkomiot.id/v2.0/pubs/APP658010f82695e25353/DEV658011363a98983712"; // Sesuai kan dengan akun masing masing
const char* AccessKey = "18c7c435c47fcf6c"; // Ganti dengan Access Key masing-masing
const char* AccessToken = "18c7c435c47aa5cf";// Ganti dengan Access Token masing-masing

////Sibolga LoRa
//const char *devAddr = "65801106"; // Ganti dengan device adrress masing masing
//const char *appSKey = "65801106185d2cddba16a901d42384e8"; // Ganti dengan Apps Key masing masing
//const char *nwkSKey = "65801106aed4c8452d59b8c692e315ec"; // Ganti dengan Nwks Key masing masing

char myStr[50];
byte outStr[255];
int port, channel, freq;
#define MSG_BUFFER_SIZE (150)
char msg[MSG_BUFFER_SIZE] = "{\"Radon\":\"%d\"}";
char pesan[150];

//const sRFM_pins RFM_pins = {
//  .CS = 5,
//  .RST = 33,
//  .DIO0 = 26,
//  .DIO1 = 27,
//};

boolean sendNow = false;
int radonValue = 0;
//int gwlValue = 0;
char* radonNotifValue;
uint8_t* pData[12];
size_t lengthDataRadon;
int radonValueBuff;
bool newDataR = false;
//bool newDataG = false;
char* receivedChars;

unsigned long previousMillis = 0;
int interval = 60 * 1000;

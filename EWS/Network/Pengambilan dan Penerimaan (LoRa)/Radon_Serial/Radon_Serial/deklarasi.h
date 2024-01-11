#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <ESP32Ping.h>
#include <esp_task_wdt.h>
#include <string.h>
#include <HardwareSerial.h>
#include <lorawan.h>
#define WDT_TIMEOUT 8

boolean sendNow = false;
int tmpradonValue = 0;
int radonValue = 0;
int sensorValue = 0;
char* radonNotifValue;
uint8_t* pData[12];
size_t lengthDataRadon;
int radonValueBuff;
String strdata;

unsigned long previousMillis = 0;
int interval = 20 * 1000;

static BLEUUID filterUUID  ("0000abf0-0000-1000-8000-00805F9B34FB"); // UART filter UUID
static BLEUUID serviceUUID ("00001523-0000-1000-8000-00805F9B34FB"); // UART customservice UUID
static BLEUUID charUUID    ("00001525-0000-1000-8000-00805F9B34FB");
static BLEUUID char24UUID  ("00001524-0000-1000-8000-00805F9B34FB");
static union {
  char c[4];
  uint32_t b;
  float f;
}
radonval;

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLERemoteCharacteristic* p2RemoteCharacteristic;
static BLERemoteService* pRemoteService;
static BLEAdvertisedDevice* myDevice;

//Sibolga LoRa
const char *devAddr = "6582fb02"; // Ganti dengan Alamat Perangkat yang Anda miliki di konsol Antares
const char *nwkSKey = "6582fb02cf3789236250c7845ef5c004"; // Ganti dengan Kunci Sesi Jaringan yang Anda miliki di konsol Antares
const char *appSKey = "6582fb02e3c7d77d3eb4c70a64e237c9"; // Ganti dengan Kunci Sesi Aplikasi yang Anda miliki di konsol Antares

char myStr[50];
char outStr[255];
byte recvStatus=0;
int port, channel, freq;
#define MSG_BUFFER_SIZE (150)
char msg[MSG_BUFFER_SIZE] = "{\"Radon\":\"%d\",\"GWL\":\"%d\"}";
char pesan[150];

const sRFM_pins RFM_pins = {
  .CS = 5,
  .RST = 33,
  .DIO0 = 26,
  .DIO1 = 27,
};

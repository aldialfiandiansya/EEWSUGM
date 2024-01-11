#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <ESP32Ping.h>
#include <esp_task_wdt.h>
#include <string.h>
#include <HardwareSerial.h>
#define WDT_TIMEOUT 8

// const int analogInPin = 35;  // Analog input pin that the potentiometer is attached to

boolean sendNow = false;
int tmpradonValue = 0;
// int tmpgwlValue = 0;
int radonValue = 0;
// int gwlValue = 0;
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

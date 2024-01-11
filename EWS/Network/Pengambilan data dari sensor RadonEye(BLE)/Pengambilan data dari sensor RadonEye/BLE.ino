static void notifyCallback(BLERemoteCharacteristic* pRemoteCharacteristic,
                           uint8_t* pData,
                           size_t lengthDataRadon,
                           bool isNotify) {
  radonValueBuff = pData[2];
}

class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient* pclient) {
    }
    void onDisconnect(BLEClient* pclient) {
      connected = false;
    }
};

bool connectToServer() {
  bool flag = true;
  BLEClient*  pClient  = BLEDevice::createClient();
  pClient->setClientCallbacks(new MyClientCallback());
  pClient->connect(myDevice);
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  p2RemoteCharacteristic = pRemoteService->getCharacteristic(char24UUID);
  if (pRemoteService == nullptr) {
    pClient->disconnect();

    flag = false;
    return false;
  }
  else if (pRemoteCharacteristic == nullptr) {
    pClient->disconnect();
    flag = false;
    return false;
  }
  else if (p2RemoteCharacteristic == nullptr) {
    pClient->disconnect();
    flag = false;
    return false;
  }
  else if (p2RemoteCharacteristic->canWriteNoResponse()) {
    p2RemoteCharacteristic->writeValue(0x50, false);
  }
  if (pRemoteCharacteristic->canNotify()) {
    const uint8_t v[] = {0x1, 0x0};
    pRemoteCharacteristic->registerForNotify(notifyCallback);
    pRemoteCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)v, 2, true);
  }
  if (flag == true && pRemoteCharacteristic->canRead()) {
    Serial.println("flag true");
    connected = true;
    return true;
  }
};

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      //if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
      if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(filterUUID)) {
        BLEDevice::getScan()->stop();
        myDevice = new BLEAdvertisedDevice(advertisedDevice);
        //myDevice = new BLEAdvertisedDevice(serviceUUID);
        doConnect = true;
        doScan = true;
        Serial.println("UUID Service cocok dan doConnect & doScan true");
      }
    }
};

void getData() {
  if (p2RemoteCharacteristic->canWriteNoResponse()) {
    p2RemoteCharacteristic->writeValue(0x50, false);
  }
  else {
    ESP.restart();
  }
  // read the analog in value:
  if (radonValueBuff > 0) {
    tmpradonValue = radonValueBuff;  // Simpan nilai jika > 0
  }
  radonValue = tmpradonValue;
  sendNow = true;
};

void bleClient() {
  Serial.println("ESP ble client Initiated");
  esp_task_wdt_reset();
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
  Serial.println("ble client ok");
  sendNow = false;
}

void sendLora() {
  Serial.print("Send Data via LoRa: ");
  Serial.print(radonValue);
  Serial.print(", ");
  sprintf(myStr, msg, radonValue);
  Serial.println(myStr);
  lora.sendUplink(myStr, strlen(myStr), 0,5);
  // port = lora.getFramePortTx();
  channel = lora.getChannel();
  // freq = lora.getChannelFreq(channel);
  Serial.print(F("fport: ")); Serial.print(port); Serial.print(" ");
  Serial.print(F("Ch: ")); Serial.print(channel); Serial.print(" ");
  Serial.print(F("Freq: ")); Serial.print(freq); Serial.println(" ");
  lora.update();
}
void initLoRa() {
  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }
  lora.setDeviceClass(CLASS_A);
  lora.setDataRate(SF10BW125);
  // lora.setFramePortTx(5);
  lora.setChannel(MULTI);
  lora.setTxPower1(15);
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);
}

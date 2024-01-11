void initwifiConnect() {
  Serial.println("Try connect to access point");
  delay(1000);
  int timeout = 0;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    timeout++;
    delay(1000);
    Serial.print(".");
    if (timeout >= 20) {
      ESP.restart();
    }
  }
  Serial.println();
}
void pingGoogle() {
  bool successPing = Ping.ping("www.google.com", 3);
  int timeout2 = 0;
  while (!successPing) {
    Serial.println("Ping failed");
    successPing = Ping.ping("www.google.com", 3);
    timeout2++;
    delay(200);
    if (timeout2 >= 50) {
      ESP.restart();
    }
  }
}

void sendDataHTTP() {
  for (int i = 0; i < 1; i++) {
    esp_task_wdt_reset();
    sprintf (pesan, msg, radonValue);
    Serial.print("Publish message: ");
    Serial.println(pesan);
    HTTPClient http;
    http.begin(http_server);
    http.addHeader("Content-Type", "text/plain");
    http.setAuthorization(AccessKey, AccessToken);
    int httpResponseCode = http.POST(pesan);   //Send the actual POST request
    if (httpResponseCode > 0) {
      String response = http.getString();                       //Get the response to the request
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();  //Free resources
  }
  esp_task_wdt_reset();
}

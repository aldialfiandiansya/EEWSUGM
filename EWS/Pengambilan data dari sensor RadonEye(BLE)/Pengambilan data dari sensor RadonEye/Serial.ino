void sendSerial() {
  int Rad = radonValue; // Contoh variabel angka
  // int jmlGwl = gwlValue;// / 10; // Contoh variabel teks
  String dataToSend = "$" + String(Rad) + "," + "#";
  Serial.println("Mengirim data: " + dataToSend);
  Serial2.println(dataToSend); // Mengirim data melalui Serial2
}

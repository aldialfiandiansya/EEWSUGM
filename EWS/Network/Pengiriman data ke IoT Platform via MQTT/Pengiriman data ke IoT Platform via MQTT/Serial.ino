void parseData() {
  char receivedChar = Serial2.read(); // Membaca karakter dari Serial2
  if (receivedChar == '$') {
    receivedData = ""; // Reset variabel receivedData jika menemukan awalan data ($)
 } else if (receivedChar == '#') {
   // Proses data setelah menemukan penutup data (#)
   processData(receivedData);
  } else {
    receivedData += receivedChar; // Menambahkan karakter ke receivedData
  }
}
void processData(String data) {
  esp_task_wdt_reset();
  // Memproses data yang telah diterima setelah dihilangkan awalan ($) dan penutup (#)
  // Misalnya, memecah string menjadi variabel-variabel angka dan teks berdasarkan karakter pemisah (koma)
  int receivedAngkaRadon = data.substring(0, data.indexOf(',')).toInt();
//  int receivedAngkaGwl = data.substring(data.indexOf(',') + 1).toInt();
    // Menampilkan data yang diterima
  Serial.print("Menerima angka Radon: ");  Serial.print(receivedAngkaRadon);
//  Serial.print(", Menerima angka GWL: ");  Serial.println(receivedAngkaGwl);
  radonValue = receivedAngkaRadon;
//  gwlValue = receivedAngkaGwl;
}

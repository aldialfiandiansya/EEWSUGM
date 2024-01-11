// void analog() {
//   int sensorValue = analogRead(analogInPin);
//   if (sensorValue > 0) {
//     tmpgwlValue = sensorValue;  // Simpan nilai jika > 0
//     // Serial.print("Sensor value stored: ");
//     // Serial.println(storedValue);
//     // Memetakan nilai dari rentang 0-500 ke nilai ADC 0-4095
//     gwlValue = map(tmpgwlValue, 0, 4095, 0, 500 );
//     Serial.print("Rerata GWL= ") ; Serial.println(gwlValue);
//   }
// }

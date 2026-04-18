#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);      // Monitor PC
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // USART

  Serial.println("Escribe algo:");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.write(c);   // enviar al otro ESP32
  }
}

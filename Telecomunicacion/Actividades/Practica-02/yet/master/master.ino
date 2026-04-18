// ESP32 DevKit - SPI Master
#include <SPI.h>

#define CS_PIN 5

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23, CS_PIN);  // SCLK, MISO, MOSI, CS
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  Serial.println("ESP32 DevKit SPI Master Listo. Escribe algo:");
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    Serial.println("[TX SPI enviado]: " + msg);

    // Enviar byte a byte y leer respuesta simultánea
    digitalWrite(CS_PIN, LOW);
    delayMicroseconds(10);

    String recibido = "";
    for (int i = 0; i < (int)msg.length(); i++) {
      byte resp = SPI.transfer(msg[i]);
      if (resp != 0xFF && resp != 0x00) {  // Filtra bytes vacíos
        recibido += (char)resp;
      }
    }
    // Enviar byte de fin
    SPI.transfer('\n');

    delayMicroseconds(10);
    digitalWrite(CS_PIN, HIGH);

    if (recibido.length() > 0) {
      Serial.println("[RX SPI recibido del Slave]: " + recibido);
    }
  }
}

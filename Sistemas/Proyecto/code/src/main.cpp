#include "hall_sensor.h"
#include <Arduino.h>
// #include "adrc_control.h"

void setup() {
  Serial.begin(115200);
  // Usamos los pines GPIO del ESP32-S3 que hayas elegido
  initHallSensors(4, 5, 6);
  Serial.println("Sensores inicializados.");
}

void loop() {
  int position = readRotorPosition();
  // calcularADRC(position);
  // setearPWM();
}

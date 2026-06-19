#include <Arduino.h>

// Definimos el pin digital que vamos a usar
const int pinSalida = 7;

void setup() {
  // Configura el pin 7 como salida de voltaje
  pinMode(pinSalida, OUTPUT);
}

void loop() {
  // 1. Activa el pin a 5V (HIGH)
  digitalWrite(pinSalida, HIGH);
  // Espera 5000 milisegundos (5 segundos)
  delay(5000);

  // 2. Apaga el pin a 0V (LOW)
  digitalWrite(pinSalida, LOW);
  // Espera otros 5000 milisegundos (5 segundos)
  delay(5000);
}

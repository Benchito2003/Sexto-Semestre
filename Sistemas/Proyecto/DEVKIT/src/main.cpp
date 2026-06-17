#include <Arduino.h>

// CAMBIO CRÍTICO 1: El pin 7 en el ESP32 es peligroso.
// Los pines GPIO del 6 al 11 están conectados internamente a la memoria Flash
// del ESP32. Si los usas, la placa entrará en pánico (crash) y se reiniciará
// constantemente. Usaremos el GPIO 2, que es 100% seguro y, en la mayoría de
// ESP32 DevKit, está conectado a un pequeño LED azul en la placa, así verás si
// funciona.
const int pinSalida = 2;

void setup() {
  // Configura el pin 2 como salida de voltaje
  pinMode(pinSalida, OUTPUT);
}

void loop() {
  // CAMBIO CRÍTICO 2: La lógica.
  // Activa el pin a 3.3V (HIGH). ¡Recuerda que el ESP32 no puede sacar 5V!
  digitalWrite(pinSalida, HIGH);

  // Espera 5000 milisegundos (5 segundos)
  delay(5000);

  // Apaga el pin a 0V (LOW)
  digitalWrite(pinSalida, LOW);

  // Espera otros 5000 milisegundos (5 segundos)
  delay(5000);
}

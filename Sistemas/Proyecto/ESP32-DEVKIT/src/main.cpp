#include <Arduino.h>

// Elegimos pines que NO sean Strapping Pins y que tengan resistencia Pull-Up
// interna. Los GPIO 25, 26 y 27 son perfectos y muy seguros.
const int pinHallA = 25;
const int pinHallB = 26;
const int pinHallC = 27;

// Usamos 'volatile' porque esta variable va a ser modificada por el hardware
// en segundo plano, sin que el loop() se dé cuenta.
volatile unsigned long contadorPulsos = 0;

// Esta es la Rutina de Interrupción (ISR).
// IRAM_ATTR obliga al ESP32 a guardar esta función en la memoria RAM ultra
// rápida en lugar de la memoria Flash, porque necesita ejecutarse en
// microsegundos.
void IRAM_ATTR contarPulso() { contadorPulsos++; }

void setup() {
  Serial.begin(115200);

  // Configuramos los pines. INPUT_PULLUP inyecta 3.3V internamente por si
  // los sensores del motor son de tipo "Open Collector" (colector abierto).
  pinMode(pinHallA, INPUT_PULLUP);
  pinMode(pinHallB, INPUT_PULLUP);
  pinMode(pinHallC, INPUT_PULLUP);

  // Le decimos al ESP32: "Pase lo que pase, si alguno de estos pines cambia
  // (CHANGE) de LOW a HIGH o de HIGH a LOW, pausa todo y ejecuta contarPulso()
  // al instante".
  attachInterrupt(digitalPinToInterrupt(pinHallA), contarPulso, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinHallB), contarPulso, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinHallC), contarPulso, CHANGE);

  Serial.println("Lector Hall iniciado. Gira el motor con la mano...");
}

void loop() {
  // Solo para visualizar, imprimimos el contador cada medio segundo
  static unsigned long ultimoTiempo = 0;
  if (millis() - ultimoTiempo >= 500) {
    Serial.print("Pulsos acumulados: ");
    Serial.println(contadorPulsos);
    ultimoTiempo = millis();
  }
}

#include "hall_sensors.h"

// Pines seguros para el ESP32-S3
const int pinHallA = 4;
const int pinHallB = 5;
const int pinHallC = 6;

// Aquí sí inicializamos la variable
volatile unsigned long contadorPulsos = 0;
volatile unsigned long ultimoTiempo = 0;

// La interrupción súper rápida
void IRAM_ATTR contarPulso() {
  unsigned long tiempoActual = micros();
  // Filtro de ruido de 1 milisegundo
  if (tiempoActual - ultimoTiempo > 1000) {
    contadorPulsos++;
    ultimoTiempo = tiempoActual;
  }
}

void initHallSensors() {
  pinMode(pinHallA, INPUT_PULLUP);
  pinMode(pinHallB, INPUT_PULLUP);
  pinMode(pinHallC, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinHallA), contarPulso, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinHallB), contarPulso, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinHallC), contarPulso, CHANGE);

  Serial.println("✅ Sensores Hall Inicializados en pines 4, 5 y 6");
}

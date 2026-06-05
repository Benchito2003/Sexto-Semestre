#include "hall_sensor.h"

void initHallSensors(int pinA, int pinB, int pinC) {
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
}

int readRotorPosition() {
  // Aquí iría tu lógica de lectura digital combinando A, B y C
  return 1; // Retorno de prueba
}

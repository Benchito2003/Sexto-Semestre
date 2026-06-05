#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include <Arduino.h> // Siempre necesario para usar tipos estándar de Arduino

// Declaramos la función que inicializará los pines
void initHallSensors(int pinA, int pinB, int pinC);

// Declaramos la función que leerá el estado actual
int readRotorPosition();

#endif

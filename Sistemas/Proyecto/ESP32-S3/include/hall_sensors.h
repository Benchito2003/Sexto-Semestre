#ifndef HALL_SENSORS_H
#define HALL_SENSORS_H

#include <Arduino.h>

// Declaramos la variable como 'extern' para que el main.cpp pueda leerla
extern volatile unsigned long contadorPulsos;

// Declaramos las funciones
void initHallSensors();

#endif

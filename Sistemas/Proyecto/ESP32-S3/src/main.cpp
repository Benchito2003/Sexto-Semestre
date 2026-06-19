#include "hall_sensors.h"
#include "pwm_driver.h"
#include <Arduino.h>

// Variables "Globales" (o static) para recordar el estado actual del latido
unsigned long ultimoTiempoPWM = 0;
int cicloDeTrabajo = 0;
int direccion = 1; // 1 significa acelerando, -1 significa frenando

void setup() {
  Serial.begin(115200);
  initHallSensors();
  initPWM();
}

void loop() {
  // 1. Miramos el reloj
  unsigned long tiempoActual = millis();

  // 2. ¿Ya pasaron 5 milisegundos?
  if (tiempoActual - ultimoTiempoPWM >= 5) {
    // Reiniciamos el cronómetro
    ultimoTiempoPWM = tiempoActual;

    // Calculamos el nuevo ancho de pulso
    cicloDeTrabajo = cicloDeTrabajo + direccion;

    // Si llegamos al máximo, invertimos la dirección hacia abajo
    if (cicloDeTrabajo >= 255) {
      cicloDeTrabajo = 255;
      direccion = -1;
    }
    // Si llegamos al mínimo, invertimos la dirección hacia arriba
    else if (cicloDeTrabajo <= 0) {
      cicloDeTrabajo = 0;
      direccion = 1;
    }

    // Enviamos la orden al hardware
    setAnchoDePulso(cicloDeTrabajo);
  }

  // 3. ¡LA MAGIA OCURRE AQUÍ!
  // Mientras no pasen esos 5 milisegundos, el ESP32 pasará por esta línea
  // millones de veces por segundo.
  // Aquí es donde pondremos tu algoritmo ADRC, la lectura de la resistencia
  // Shunt y las alarmas de seguridad, ¡y nada se quedará esperando!
}

#include "pwm_driver.h"

// Usamos 'static' para que estas variables sean PRIVADAS.
// Nadie fuera de este archivo puede tocarlas ni romperlas.
static const int pinPWM = 2; // El LED azul del ESP32-S3 para probar
static const int canalPWM = 0;
static const int frecuencia =
    20000; // 20kHz, ideal para no escuchar un pitido en el motor
static const int resolucion = 8; // Valores de 0 a 255

void initPWM() {
  // Configuración del hardware interno del ESP32
  ledcSetup(canalPWM, frecuencia, resolucion);
  ledcAttachPin(pinPWM, canalPWM);
  Serial.println("✅ Módulo PWM Inicializado (Hardware Timer a 20kHz)");
}

void setAnchoDePulso(int valorPWM) {
  // Filtro de seguridad: Evitamos que por un error matemático del ADRC
  // le mandemos un valor fuera de rango al hardware.
  if (valorPWM > 255)
    valorPWM = 255;
  if (valorPWM < 0)
    valorPWM = 0;

  // Actualizamos la señal física
  ledcWrite(canalPWM, valorPWM);
}

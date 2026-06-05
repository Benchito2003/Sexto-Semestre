#include <Arduino.h>

// --- Configuración de Pines para ESP32 ---
const int VRx = 34;      // Pin analógico (ADC1_CH6) para el eje X del Joystick
const int motorIzq = 18; // Pin GPIO para motor vibrador izquierdo (Soporta PWM)
const int motorDer = 19; // Pin GPIO para motor vibrador derecho (Soporta PWM)

// --- Variables para control de tiempo (Manejo sin delay) ---
unsigned long tiempoActual;
unsigned long tiempoAnteriorX = 0;
unsigned long periodoX = 0;

// --- Constantes de velocidad (Periodo en milisegundos entre envíos) ---
const unsigned long VEL_BAJA = 400;
const unsigned long VEL_MEDIA = 200;
const unsigned long VEL_ALTA = 50;

// --- Constantes para Intensidad de Vibración (PWM de 0 a 255) ---
const int VIB_BAJA = 100;
const int VIB_MEDIA = 175;
const int VIB_ALTA = 255;
const int VIB_NULA = 0;

void setup() {
  // Nota: Mantenemos 9600 bps si el software ComandosRS232 lo requiere
  // obligatoriamente. Si modificas esto, recuerda actualizar el 'monitor_speed'
  // en tu platformio.ini
  Serial.begin(9600);

  // Configuración del pin analógico en el ESP32 (Opcional pero recomendado para
  // asegurar 12 bits)
  analogReadResolution(12);
  pinMode(VRx, INPUT);

  // Configuración de pines de los motores
  pinMode(motorIzq, OUTPUT);
  pinMode(motorDer, OUTPUT);

  // Asegurarnos de que inician apagados
  analogWrite(motorIzq, VIB_NULA);
  analogWrite(motorDer, VIB_NULA);
}

void loop() {
  tiempoActual = millis();

  // ---------------------------------------------------------
  // 1. LECTURA DE COMANDOS SERIE (Retroalimentación Háptica)
  // ---------------------------------------------------------
  if (Serial.available() > 0) {
    int comandoRecibido = Serial.read();

    switch (comandoRecibido) {
    // --- Desviación hacia la Izquierda ---
    case 50: // BAJA IZQUIERDA
      analogWrite(motorIzq, VIB_BAJA);
      analogWrite(motorDer, VIB_NULA);
      break;
    case 60: // MEDIA IZQUIERDA
      analogWrite(motorIzq, VIB_MEDIA);
      analogWrite(motorDer, VIB_NULA);
      break;
    case 70: // ALTA IZQUIERDA
      analogWrite(motorIzq, VIB_ALTA);
      analogWrite(motorDer, VIB_NULA);
      break;

    // --- Desviación hacia la Derecha ---
    case 80: // BAJA DERECHA
      analogWrite(motorIzq, VIB_NULA);
      analogWrite(motorDer, VIB_BAJA);
      break;
    case 90: // MEDIA DERECHA
      analogWrite(motorIzq, VIB_NULA);
      analogWrite(motorDer, VIB_MEDIA);
      break;
    case 100: // ALTA DERECHA
      analogWrite(motorIzq, VIB_NULA);
      analogWrite(motorDer, VIB_ALTA);
      break;

    // --- Sin Desviación ---
    case 200:
      analogWrite(motorIzq, VIB_NULA);
      analogWrite(motorDer, VIB_NULA);
      break;
    }
  }

  // ---------------------------------------------------------
  // 2. LECTURA DEL JOYSTICK Y ENVÍO DE COMANDOS (Control Vehículo)
  // ---------------------------------------------------------
  int X = analogRead(VRx);
  int estadoX = 0; // 0: Centro, 1: Derecha (10), -1: Izquierda (20)

  // Escala de lectura en ESP32: 0 a 4095. El centro teórico está cerca de 2048.

  // Evaluar hacia la DERECHA (Valores mayores al centro con zona muerta)
  if (X > 2200) {
    estadoX = 1;
    if (X < 2800) {
      periodoX = VEL_BAJA;
    } else if (X < 3600) {
      periodoX = VEL_MEDIA;
    } else {
      periodoX = VEL_ALTA;
    }
  }
  // Evaluar hacia la IZQUIERDA (Valores menores al centro)
  else if (X < 1800) {
    estadoX = -1;
    if (X > 1200) {
      periodoX = VEL_BAJA;
    } else if (X > 400) {
      periodoX = VEL_MEDIA;
    } else {
      periodoX = VEL_ALTA;
    }
  }

  // Gestión del envío de comandos por el puerto serie sin bloquear el flujo
  if (estadoX != 0) {
    if (tiempoActual - tiempoAnteriorX >= periodoX) {
      if (estadoX == 1) {
        Serial.write(10); // Comando para mover a la derecha la animación
      } else if (estadoX == -1) {
        Serial.write(20); // Comando para mover a la izquierda la animación
      }
      tiempoAnteriorX = tiempoActual;
    }
  }
}

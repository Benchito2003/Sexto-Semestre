#include <Arduino.h>

// --- Configuración de Pines para ESP32 ---
const int VRx = 34;       // Pin analógico (ADC1_CH6) para el eje X del Joystick
const int motorIzq = 18;  // Pin GPIO para motor vibrador izquierdo (Soporta PWM)
const int motorDer = 19;  // Pin GPIO para motor vibrador derecho (Soporta PWM)

// --- Variables para control de tiempo ---
unsigned long tiempoActual;
unsigned long tiempoAnteriorX = 0;
unsigned long periodoX = 0;

// --- Constantes de velocidad (Periodo en milisegundos entre envíos) ---
// Tiempos reducidos para incrementar la agilidad de respuesta
const unsigned long VEL_BAJA = 300;   // Antes 400
const unsigned long VEL_MEDIA = 120;  // Antes 200
const unsigned long VEL_ALTA = 30;    // Antes 50
const unsigned long VEL_TURBO = 8;    // Antes 15

// --- Constantes para Intensidad de Vibración (PWM de 0 a 255) ---
const int VIB_BAJA = 100;
const int VIB_MEDIA = 175;
const int VIB_ALTA = 255;
const int VIB_NULA = 0;

void setup() {
  Serial.begin(115200);

  // Configuración del pin analógico en el ESP32 (Resolución a 12 bits: 0-4095)
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

  // 1. LECTURA DE COMANDOS SERIE (Retroalimentación Háptica)
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

  // 2. LECTURA DEL JOYSTICK Y ENVÍO DE COMANDOS (Control Vehículo)
  int X = analogRead(VRx);
  int estadoX = 0;         // 0: Centro, 1: Derecha (10), -1: Izquierda (20)
  
  // Evaluar hacia la DERECHA
  if (X > 2200) {
    estadoX = 1; 
    if (X < 2800) {
      periodoX = VEL_BAJA;
    } else if (X < 3400) {
      periodoX = VEL_MEDIA;
    } else if (X < 3900) {
      periodoX = VEL_ALTA;
    } else {
      periodoX = VEL_TURBO; // Palanca totalmente a la derecha
    }
  } 
  // Evaluar hacia la IZQUIERDA
  else if (X < 1800) {
    estadoX = -1; 
    if (X > 1200) {
      periodoX = VEL_BAJA;
    } else if (X > 600) {
      periodoX = VEL_MEDIA;
    } else if (X > 150) {
      periodoX = VEL_ALTA;
    } else {
      periodoX = VEL_TURBO; // Palanca totalmente a la izquierda
    }
  }

  // Gestión del envío de comandos por el puerto serie
  if (estadoX != 0) {
    if (tiempoActual - tiempoAnteriorX >= periodoX) {
      if (estadoX == 1) {
        Serial.write(10); // Comando para mover a la derecha
      } else if (estadoX == -1) {
        Serial.write(20); // Comando para mover a la izquierda
      }
      tiempoAnteriorX = tiempoActual;
    }
  }
}

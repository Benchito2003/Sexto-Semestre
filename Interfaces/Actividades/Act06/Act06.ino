#include <Arduino.h>

// --- Configuración de Pines para ESP32 ---
const int VRy = 34;       // Pin analógico (ADC1_CH6) para el eje y del Joystick
const int motorIzq = 18;  // Pin GPIO para motor vibrador izquierdo (Soporta PWM)
const int motorDer = 19;  // Pin GPIO para motor vibrador derecho (Soporta PWM)

// --- Variables para control de tiempo ---
unsigned long tiempoActual;
unsigned long tiempoAnteriorY = 0;
unsigned long periodoY = 0;

// --- Constantes de velocidad (Periodo en milisegundos entre envíos) ---
const unsigned long VEL_BAJA = 300;
const unsigned long VEL_MEDIA = 120;
const unsigned long VEL_ALTA = 30;
const unsigned long VEL_TURBO = 8;

// --- Constantes para Intensidad de Vibración (PWM de 0 a 255) ---
const int VIB_BAJA = 100;
const int VIB_MEDIA = 175;
const int VIB_ALTA = 255;
const int VIB_NULA = 0;

void setup() {
  Serial.begin(115200);

  // Configuración del pin analógico en el ESP32 (Resolución a 12 bits: 0-4095)
  analogReadResolution(12); 
  pinMode(VRy, INPUT);
  
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
  int Y = analogRead(VRy);
  int estadoY = 0;         // 0: Centro, 1: Derecha (10), -1: Izquierda (20)
  
  // Evaluar hacia la DERECHA
  if (Y > 2200) {
    estadoY = 1; 
    if (Y < 2800) {
      periodoY = VEL_BAJA;
    } else if (Y < 3400) {
      periodoY = VEL_MEDIA;
    } else if (Y < 3900) {
      periodoY = VEL_ALTA;
    } else {
      periodoY = VEL_TURBO; // Palanca totalmente a la derecha
    }
  } 
  // Evaluar hacia la IZQUIERDA
  else if (Y < 1800) {
    estadoY = -1; 
    if (Y > 1200) {
      periodoY = VEL_BAJA;
    } else if (Y > 600) {
      periodoY = VEL_MEDIA;
    } else if (Y > 150) {
      periodoY = VEL_ALTA;
    } else {
      periodoY = VEL_TURBO; // Palanca totalmente a la izquierda
    }
  }

  // Gestión del envío de comandos por el puerto serie
  if (estadoY != 0) {
    if (tiempoActual - tiempoAnteriorY >= periodoX) {
      if (estadoY == 1) {
        Serial.write(10); // Comando para mover a la derecha
      } else if (estadoY == -1) {
        Serial.write(20); // Comando para mover a la izquierda
      }
      tiempoAnteriorY = tiempoActual;
    }
  }
}

// Código desarrollado por Flores Montero Edsel Yetlanezi && Rubén Alfonso Gamboa
// Pensado para ESP32 clásico con el sensor inercial MPU6050

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "BluetoothSerial.h"

// Pines de comunicación para la ESP32
#define I2C_SDA 21
#define I2C_SCL 22
#define BOTON_BOOT 0 

Adafruit_MPU6050 mpu;
BluetoothSerial SerialBT;

// ====================================================================
// =                     ZONA DE CONFIGURACIÓN                        =
// ====================================================================
//
int sensibilidad_X_IzquierdaDerecha = 80; 
int sensibilidad_Y_ArribaAbajo = 80; 
float sensibilidad_Rotacion = 6.0; 

unsigned long intervalo_muestreo = 8;    // Leemos el sensor cada 8 milisegundos
unsigned long intervalo_envio = 24;      // Enviamos datos al PC cada 24 milisegundos
unsigned long cooldown_seleccion = 700;  // Espera (en ms) entre cada "clic" para evitar clics dobles accidentales
float suavizado_movimiento = 0.10;       // Qué tan suave se mueve (menor = más suave, pero con un poco más de lag)
// ====================================================================

// --- Variables internas  ---
float umbral_grados_X;
float umbral_grados_Y;
float offset_Pitch_Nod = 0;
float offset_Roll_Doorknob = 0;

// Variables para el control de tiempo
unsigned long tiempo_ultimo_muestreo = 0;
unsigned long tiempo_ultimo_envio = 0;
unsigned long tiempo_ultima_seleccion = 0;

// Ángulos ya procesados y libres de temblores
float anguloX_filtrado = 0;
float anguloY_filtrado = 0;

// --- Sistema de calibración sin pausas ---
bool calibrando_centro = false;
int muestras_tomadas = 0;
float suma_Pitch_calibracion = 0;
float suma_Roll_calibracion = 0;
unsigned long tiempo_ultima_muestra_calibracion = 0;


// Convierte tu número del 1 al 100 en grados reales de inclinación para el sensor
float calcularUmbralAngulo(int sensibilidad) {
  sensibilidad = constrain(sensibilidad, 1, 100);
  return map(sensibilidad, 1, 100, 600, 20) / 10.0; 
}

// Prepara el sistema para empezar a calibrar el "centro" de tu mano
void iniciarCalibracion() {
  calibrando_centro = true;
  muestras_tomadas = 0;
  suma_Pitch_calibracion = 0;
  suma_Roll_calibracion = 0;
  
  // Reiniciamos los ángulos para evitar saltos locos en la pantalla
  anguloX_filtrado = 0;
  anguloY_filtrado = 0;
}

void setup() {
  // Iniciamos el Bluetooth con el nombre que buscarás en tu computadora
  SerialBT.begin("Sensor_Mano_Biomedica");
  
  pinMode(BOTON_BOOT, INPUT_PULLUP);
  Wire.begin(I2C_SDA, I2C_SCL);

  // Si el sensor MPU6050 no está bien conectado, nos quedamos esperando aquí
  if (!mpu.begin(0x68, &Wire)) {
    while (1) { ; } 
  }
  
  // Configuramos el sensor para detectar los movimientos humanos típicos
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 
  mpu.setSampleRateDivisor(7);

  // Calculamos cuánto tiene que girar la mano para registrar un movimiento
  umbral_grados_X = calcularUmbralAngulo(sensibilidad_X_IzquierdaDerecha);
  umbral_grados_Y = calcularUmbralAngulo(sensibilidad_Y_ArribaAbajo);

  // Al encender la placa, calibramos la posición inicial automáticamente
  iniciarCalibracion();
}

void loop() {
  unsigned long tiempo_actual = millis();

  // Si presionas el botón BOOT de la ESP32, re-calibramos el centro
  // (Solo lo hacemos si no estamos ya calibrando)
  if (digitalRead(BOTON_BOOT) == LOW && !calibrando_centro) {
    iniciarCalibracion();
  }

  // ====================================================================
  // 1. FASE DE CALIBRACIÓN (Silenciosa y sin trabar la placa)
  // ====================================================================
  if (calibrando_centro) {
    
    // Tomamos una muestra cada 10 milisegundos hasta juntar 15
    if (tiempo_actual - tiempo_ultima_muestra_calibracion >= 10) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      // Vamos acumulando las lecturas para sacar un promedio después
      suma_Pitch_calibracion += atan2(a.acceleration.y, sqrt(sq(a.acceleration.x) + sq(a.acceleration.z))) * RAD_TO_DEG;
      suma_Roll_calibracion  += atan2(a.acceleration.x, sqrt(sq(a.acceleration.y) + sq(a.acceleration.z))) * RAD_TO_DEG;
      
      muestras_tomadas++;
      tiempo_ultima_muestra_calibracion = tiempo_actual;

      // ¡Listo! Ya tenemos las 15 muestras, sacamos el promedio y terminamos
      if (muestras_tomadas >= 15) {
        offset_Pitch_Nod = suma_Pitch_calibracion / 15.0;
        offset_Roll_Doorknob = suma_Roll_calibracion / 15.0;
        calibrando_centro = false; // Salimos del modo calibración
      }
    }
    // Mientras estemos calibrando, no queremos hacer nada más en el loop, así que saltamos al inicio
    return; 
  }

  // ====================================================================
  // 2. FASE DE LECTURA NORMAL DEL SENSOR
  // ====================================================================
  if (tiempo_actual - tiempo_ultimo_muestreo >= intervalo_muestreo) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Detectamos si hubo un giro o sacudida rápida (lo usamos como "clic")
    float magnitud_giro = sqrt(sq(g.gyro.x) + sq(g.gyro.y) + sq(g.gyro.z));
    
    if (magnitud_giro > sensibilidad_Rotacion) {
      // Validamos el tiempo de espera (cooldown) para no enviar 10 clics en un segundo sin querer
      if (tiempo_actual - tiempo_ultima_seleccion >= cooldown_seleccion) {
        SerialBT.write(50); // Enviamos la señal de "clic" o "selección"
        tiempo_ultima_seleccion = tiempo_actual;
      }
    }

    // Calculamos la inclinación actual de la mano
    float pitch_crudo = atan2(a.acceleration.y, sqrt(sq(a.acceleration.x) + sq(a.acceleration.z))) * RAD_TO_DEG;
    float roll_crudo  = atan2(a.acceleration.x, sqrt(sq(a.acceleration.y) + sq(a.acceleration.z))) * RAD_TO_DEG;
    
    // Le restamos el centro que calibramos para saber cuánto nos movimos desde la posición inicial
    float lecturaX = roll_crudo - offset_Roll_Doorknob; 
    float lecturaY = pitch_crudo - offset_Pitch_Nod;   

    // Filtro para suavizar: mezcla un porcentaje del movimiento nuevo con el movimiento anterior
    // Esto quita el temblor natural del pulso humano
    anguloX_filtrado = (suavizado_movimiento * lecturaX) + ((1.0 - suavizado_movimiento) * anguloX_filtrado);
    anguloY_filtrado = (suavizado_movimiento * lecturaY) + ((1.0 - suavizado_movimiento) * anguloY_filtrado);

    tiempo_ultimo_muestreo = tiempo_actual;
  }

  // ====================================================================
  // 3. FASE DE ENVÍO POR BLUETOOTH AL PC
  // ====================================================================
  if (tiempo_actual - tiempo_ultimo_envio >= intervalo_envio) {
    
    // Movimiento Arriba / Abajo (Eje Y)
    if (anguloY_filtrado > umbral_grados_Y) {
      SerialBT.write(30); 
    } 
    else if (anguloY_filtrado < -umbral_grados_Y) {
      SerialBT.write(40); 
    }

    // Movimiento Izquierda / Derecha (Eje X)
    if (anguloX_filtrado > umbral_grados_X) {
      SerialBT.write(10); 
    } 
    else if (anguloX_filtrado < -umbral_grados_X) {
      SerialBT.write(20); 
    }

    tiempo_ultimo_envio = tiempo_actual;
  }
}

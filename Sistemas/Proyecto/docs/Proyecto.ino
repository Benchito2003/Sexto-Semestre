#include <HX711_ADC.h>
#include <EEPROM.h>

// Pines de conexión (Exactamente como en el video)
const int HX711_dout = 4; // MCU > HX711 dout pin
const int HX711_sck = 5;  // MCU > HX711 sck pin

// Constructor de la librería
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0; // Dirección de EEPROM para guardar la calibración
unsigned long t = 0;

void setup() {
  Serial.begin(57600); // ADVERTENCIA: Debes poner el Monitor Serie a esta velocidad
  delay(10);
  Serial.println();
  Serial.println("Iniciando...");

  LoadCell.begin();
  
  unsigned long stabilizingtime = 2000; // Tiempo para que la señal se estabilice al encender
  boolean _tare = true; // Realizar tara inicial
  LoadCell.start(stabilizingtime, _tare);
  
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, revisa el cableado entre el Arduino y el HX711");
    while (1);
  }
  else {
    LoadCell.setCalFactor(1.0); // Factor inicial de calibración por defecto
    Serial.println("Inicio completado.");
    
    // Iniciar automáticamente la rutina de calibración al arrancar
    calibrate();
  }
}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; 

  // Revisar si hay nuevos datos
  if (LoadCell.update()) newDataReady = true;

  // Imprimir los datos cuando estén listos
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      Serial.print("Salida de la celda de carga: ");
      Serial.println(i);
      newDataReady = 0;
      t = millis();
    }
  }

  // Recibir comandos desde el monitor serie
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay(); // Tara manual
    else if (inByte == 'r') calibrate(); // Volver a calibrar
  }

  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tara completada");
  }
}

void calibrate() {
  Serial.println("***");
  Serial.println("Iniciando calibracion:");
  Serial.println("Coloca la celda de carga en una superficie estable y nivelada.");
  Serial.println("Retira cualquier peso aplicado a la celda.");
  Serial.println("Envia la letra 't' desde el monitor serie para establecer el punto cero (tara).");

  boolean _resume = false;
  while (_resume == false) {
    LoadCell.update();
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 't') LoadCell.tareNoDelay();
    }
    if (LoadCell.getTareStatus() == true) {
      Serial.println("Tara completada.");
      _resume = true;
    }
  }

  Serial.println("Ahora, coloca un peso conocido sobre la celda de carga.");
  Serial.println("Luego envia el valor de ese peso (ej. 20.0) desde el monitor serie.");

  float known_mass = 0;
  _resume = false;
  while (_resume == false) {
    LoadCell.update();
    if (Serial.available() > 0) {
      known_mass = Serial.parseFloat();
      if (known_mass != 0) {
        Serial.print("El peso conocido es: ");
        Serial.println(known_mass);
        _resume = true;
      }
    }
  }

  LoadCell.refreshDataSet(); 
  float newCalibrationValue = LoadCell.getNewCalibration(known_mass); 

  Serial.print("El nuevo valor de calibracion es: ");
  Serial.print(newCalibrationValue);
  Serial.println(". Usa este valor (calFactor) en tu codigo final.");
  Serial.print("¿Deseas guardar este valor en la direccion EEPROM ");
  Serial.print(calVal_eepromAdress);
  Serial.println("? y/n (si/no)");

  _resume = false;
  while (_resume == false) {
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 'y') {
        EEPROM.put(calVal_eepromAdress, newCalibrationValue);
        Serial.print("Valor ");
        Serial.print(newCalibrationValue);
        Serial.println(" guardado en la EEPROM.");
        _resume = true;
      }
      else if (inByte == 'n') {
        Serial.println("Valor NO guardado en la EEPROM.");
        _resume = true;
      }
    }
  }
  Serial.println("Fin de la calibracion.");
  Serial.println("***");
}

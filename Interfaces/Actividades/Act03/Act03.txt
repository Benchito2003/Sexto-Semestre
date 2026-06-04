#include <math.h>
// --- Variables y constantes ---
// Pines
int VRx = A1;
int VRy = A2;
int SW = 7;

// Joystick
int X;
int Y;
bool boton;

// Variables para tiempo
unsigned long tiempoActual;
unsigned long tiempoAnteriorX = 0;
unsigned long tiempoAnteriorY = 0; // cada coordenada guardará su ultimo cambio por aparte

// variables para periodos y frecuencias
unsigned long periodoX;
unsigned long periodoY;
int frecuenciaX;
int frecuenciaY;

// Variables que nos permitiran 'guardar' el estado del joystick
int estadoX;
int estadoY;
bool estadoSW = false;

// constantes de los valores que toma el joystick cuando se encuentra en el centro
const int medioX = 496;
const int medioY = 524;

// constante para modificar la frecuencia maxima
const float frecMax = 150; // constante que nos ayuda a regular la velocidad, siendo una lentitud constante
const int asceleracion = 4;
const float tolerancia = 0.02;

// --- Funciones ---

// Funcion que convierte la posicion del joystick en frecuencia
float frec(int posicion){
  int absoluto = abs(511 - posicion);
  float frecuencia = pow(absoluto, asceleracion);
  float reductor = frecMax / pow(511, asceleracion);
  return frecuencia * reductor;
}


// Funcion para calcular direccion
int direction(int posicion, int valorMedio){
  if (posicion < (valorMedio - (valorMedio* tolerancia))){
    return -1; // bajar
  }
  else if (posicion <= (valorMedio + (valorMedio* tolerancia))){
    return 0; // pararse
  }
  else if (posicion > (valorMedio + (valorMedio*tolerancia))){
    return 1; // subir
  }
  else{
    return 2; // error
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Pines para lectura X y Y (analogicos)
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  // Pines para lectura de cuando se presiona el boton del joystick (digital)
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  //medicion del tiempo
  tiempoActual = millis();

  // Capturamos la posicion del Joystick
  X = analogRead(VRx);
  Y = analogRead(VRy);
  boton = digitalRead(SW);
  
  // Verificamos si se ha cambiado de posicion den alguno de los valores
  estadoX = direction(X, medioX);
  estadoY = direction(Y, medioY);

  // Mover X
  if (estadoX != 0){
    // solo si la dirección es diferente de 0, calculamos el periodo de cambio
    periodoX = 1000 / frec(X);// 1000 milis = 1 seg
    if (tiempoActual - tiempoAnteriorX >= periodoX){
      switch (estadoX){
        case -1:
          Serial.write (20);
          break;
        case 1: 
          Serial.write (10);
          break;
        case 2:
          Serial.println("Error de medicion en X");
          break;
      }
      tiempoAnteriorX = tiempoActual;
    }
  }

        
  // Mover Y
  if (estadoY != 0){
    // solo si la dirección es diferente de 0, calculamos el periodo de cambio
    periodoY = 1000 / frec(Y);// 1000 milis = 1 seg
    if (tiempoActual - tiempoAnteriorY >= periodoY){
      switch (estadoY){
        case -1:
          Serial.write (30);
          break;
        case 1: 
          Serial.write (40);
          break;
        case 2:
          Serial.println("Error de medicion en Y");
          break;
      }
      tiempoAnteriorY = tiempoActual;
    }
  }

  // Imprimir 50 cuando se presione el botón
  if (!boton){
    if (estadoSW){
      //Serial.println("presionado"); // debug
      estadoSW = false;
    }
  }
  else{
    if (!estadoSW){
      //Serial.println("Sin presionar"); // debug
      Serial.write(50);
      estadoSW = true;
    }
    
  }

}

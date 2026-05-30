//  librería: RevEng_PAJ7620
#include "RevEng_PAJ7620.h"
// Crea objeto para manejar sensor de gestos
RevEng_PAJ7620 sensor = RevEng_PAJ7620();
//variable para recibir los datos del gesto detectado
Gesture gesto; 
long tiempo;
// *********************************************************************
void setup()
{
  Serial.begin(115200);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,OUTPUT);
  Serial.println("PROGRAMA DE PRUEBA PARA PAJ7620.");
    
  if( !sensor.begin() )           // return value of 0 == success
  {
    Serial.print("ERROR AL INICIALIZAR PAJ7620...");
    while(true) { }
  }

  Serial.println("PAJ7620 INICIALIZADO CORRECTAMENTE...");
  Serial.println("PUEDE INICIAR LA GENERACION DE GESTOS...");
}

void loop()
{   
  if(digitalRead(2)==0)
    {
    digitalWrite(3,HIGH);
    gesto = sensor.readGesture();   // Read back current gesture (if any) of type Gesture
    Serial.print("GESTO:");
    Serial.println(gesto);
    tiempo=0;
    while(digitalRead(2)==0 && tiempo<100000L) tiempo++;
    digitalWrite(3,LOW);
    } 
}

String nombre = "";
String mensaje = "";
bool nombreListo = false;

void setup() {

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); 

  Serial.println("===== CHAT ESP32 =====");
  Serial.println("Escribe tu nombre y presiona ENTER:");
}

void loop() {

  //lee lo que escribe el usuario
  while (Serial.available()) {

    char c = Serial.read();

    if (c == '\r' || c == '\n') {

      if (mensaje.length() == 0) return;

      if (!nombreListo) {

        nombre = mensaje;
        nombreListo = true;
        mensaje = "";

        Serial.print("Bienvenido ");
        Serial.println(nombre);
        Serial.println("Mensaje:");

      } 
      else {

        //envia mensaje al ESP32
        Serial2.print(nombre);
        Serial2.print(": ");
        Serial2.println(mensaje);

        mensaje = "";
      }

    } 
    else {

      mensaje += c;
    }
  }
  while (Serial2.available()) {

    char c = Serial2.read();
    Serial.write(c);
  }
}

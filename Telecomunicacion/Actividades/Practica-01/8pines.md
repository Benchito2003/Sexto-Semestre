// Pines del bus de 8 bits
const int bus[8] = {4,16,17,18,19,21,22,23};

String buffer = "";
bool modoEscritura = false;

/// --- Funciones ---

// --------------------
// CAMBIAR MODOS
// --------------------

void setModoEscritura() {
  for(int i=0;i<8;i++){
    pinMode(bus[i], OUTPUT);
  }
  modoEscritura = true;
  Serial.println("Modo escritura");
}

void setModoLectura() {
  for(int i=0;i<8;i++){
    pinMode(bus[i], INPUT_PULLDOWN);
  }
  modoEscritura = false;
  Serial.println("Modo lectura");
}


// --------------------
// ENVIAR CHAR
// --------------------

void enviarChar(char c){

  for(int i=0;i<8;i++){
    int bit = (c >> (7-i)) & 1;
    digitalWrite(bus[i], bit);
  }

  delay(20); // tiempo para que el otro ESP32 lea
}


// --------------------
// LEER CHAR
// --------------------

char leerChar(){

  char c = 0;

  for(int i=0;i<8;i++){
    int bit = digitalRead(bus[i]);
    c |= bit << (7-i);
  }

  return c;
}


// --------------------
// ENVIAR STRING
// --------------------

void enviarString(String s){

  for(int i=0;i<s.length();i++){
    enviarChar(s[i]);
  }

  enviarChar('\n'); // marca fin de mensaje
}


// --------------------
// SETUP
// --------------------

void setup(){

  Serial.begin(115200);

  setModoLectura();

  Serial.println("Comandos:");
  Serial.println("w = modo escritura");
  Serial.println("r = modo lectura");
}


// --------------------
// LOOP
// --------------------
char ultimo = 0;

void loop(){

  if(Serial.available()){

    String input = Serial.readStringUntil('\n');

    if(input == "w"){
      setModoEscritura();
      return;
    }

    if(input == "r"){
      setModoLectura();
      return;
    }

    if(modoEscritura){
      enviarString(input);
      Serial.println("Enviado: " + input);
    }

  }

  if(!modoEscritura){

    char c = leerChar();

    if(c != ultimo){

      ultimo = c;

      if(c == '\n'){
        Serial.println("Recibido: " + buffer);
        buffer = "";
      }
      else{
        buffer += c;
      }

    }

  }

  delay(20);
}


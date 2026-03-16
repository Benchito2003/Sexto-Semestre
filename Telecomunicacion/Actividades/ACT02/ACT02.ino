// --- PINES DE TRANSMISIÓN (TX) ---
// Estos pines envían datos hacia el otro ESP32
const int txBus[8] = {2, 4, 5, 13, 14, 15, 16, 33};
const int txClock = 17; // El pin que avisa "¡Dato listo!"

// --- PINES DE RECEPCIÓN (RX) ---
// Estos pines escuchan los datos del otro ESP32
const int rxBus[8] = {18, 19, 21, 22, 23, 25, 26, 27};
const int rxClock = 32; // Escucha el aviso del otro ESP32

bool ultimoEstadoReloj = LOW;

void setup() {
  Serial.begin(115200);

  // Configurar Transmisión
  for(int i=0; i<8; i++){
    pinMode(txBus[i], OUTPUT);
    digitalWrite(txBus[i], LOW);
  }
  pinMode(txClock, OUTPUT);
  digitalWrite(txClock, LOW);

  // Configurar Recepción (Mantenemos los PULLDOWN que arreglaron el ruido)
  for(int i=0; i<8; i++){
    pinMode(rxBus[i], INPUT_PULLDOWN);
  }
  pinMode(rxClock, INPUT_PULLDOWN);

  Serial.println("\n--- Chat Instantáneo Iniciado ---");
}

void enviarChar(char c) {
  // 1. Colocamos los 8 bits en los cables
  for(int i=0; i<8; i++){
    int bit = (c >> (7-i)) & 1;
    digitalWrite(txBus[i], bit);
  }
  
  // 2. Disparamos el pulso de reloj (Avisamos al otro ESP32)
  digitalWrite(txClock, HIGH);
  delay(2); // Esperamos 2 milisegundos para que el otro lado reaccione
  digitalWrite(txClock, LOW);
  delay(2);
}

char leerChar() {
  char c = 0;
  for(int i=0; i<8; i++){
    int bit = digitalRead(rxBus[i]);
    c |= bit << (7-i);
  }
  return c;
}

void loop() {
  // --- ZONA DE TRANSMISIÓN ---
  // Si tú escribes algo en tu terminal...
  if(Serial.available()){
    char c = Serial.read(); // Leemos la tecla pulsada
    enviarChar(c);          // La mandamos por los cables al instante
    Serial.print(c);        // La dibujamos en nuestra propia pantalla
  }

  // --- ZONA DE RECEPCIÓN ---
  bool estadoActualReloj = digitalRead(rxClock);
  
  // Si el pin de reloj del otro ESP32 acaba de encenderse (Flanco de subida)...
  if(estadoActualReloj == HIGH && ultimoEstadoReloj == LOW){
    char c = leerChar();    // Leemos los 8 pines
    Serial.print(c);        // La dibujamos inmediatamente al lado de lo que haya
  }
  
  ultimoEstadoReloj = estadoActualReloj;
}


int botonUp = 2; //pin 2 para sumar
int botonDown = 3; // pin 3 para restar

int valor = 0;

// --- Variables para guardar tiempo, usamos unigned porque sologuardaremos númreos positivos
unsigned long tiempoInicioUp = 0;
unsigned long tiempoInicioDown = 0;

unsigned long ultimoCambioUp = 0;
unsigned long ultimoCambioDown = 0;

// Variables que funcionaran como banderas para indicar cuando se presiona un boton
bool upPresionado = false;
bool downPresionado = false;

// Función para calcular el tiempo entre un momento a otro (devuelve milisegundos a usar)
int calcularIntervalo(unsigned long tiempo) {

  if (tiempo < 500) return 400;
  if (tiempo < 2000) return 200;
  if (tiempo < 4000) return 100;

  return 50;
}

void setup() {

  Serial.begin(9600);

  pinMode(botonUp, INPUT);
  pinMode(botonDown, INPUT);
}

void loop() {

  bool up = digitalRead(botonUp);
  bool down = digitalRead(botonDown);

  unsigned long ahora = millis();

  // Si ambos se presionan no hacer nada
  if (up && down) {
    upPresionado = false;
    downPresionado = false;
    return;
  }

  // si se presiona el BOTON UP
  if (up) {

    if (!upPresionado) {
      tiempoInicioUp = ahora;
      ultimoCambioUp = ahora;
      upPresionado = true;
    }

    unsigned long tiempoPresionado = ahora - tiempoInicioUp;

    int intervalo = calcularIntervalo(tiempoPresionado);

    if (ahora - ultimoCambioUp >= intervalo) {

      valor++;
      Serial.println(valor);

      ultimoCambioUp = ahora;
    }

  } else {

    upPresionado = false;
  }

  //si se presiona el BOTON DOWN
  if (down) {

    if (!downPresionado) {
      tiempoInicioDown = ahora;
      ultimoCambioDown = ahora;
      downPresionado = true;
    }

    unsigned long tiempoPresionado = ahora - tiempoInicioDown;

    int intervalo = calcularIntervalo(tiempoPresionado);

    if (ahora - ultimoCambioDown >= intervalo) {

      valor--;
      Serial.println(valor);

      ultimoCambioDown = ahora;
    }

  } else {

    downPresionado = false;
  }
}


#include <SPI.h>
#include "driver/spi_slave.h"

// ─── Pines ────────────────────────────────────────────────
#define PIN_SCK      18
#define PIN_MISO     19
#define PIN_MOSI     23
#define PIN_CS        5
#define PIN_BUS_BUSY  4

// ─── Parámetros ───────────────────────────────────────────
#define MAX_REINTENTOS  5
#define DELAY_BASE_MS  10
#define TIMEOUT_TX_MS  200
#define BUF_SIZE       64

// ─── Buffers (deben estar en DMA-capable memory) ──────────
static uint8_t tx_buf[BUF_SIZE];
static uint8_t rx_buf[BUF_SIZE];

bool hayMensajePendiente = false;
String colaEnvio = "";

// ──────────────────────────────────────────────────────────
//  Callbacks del driver esclavo (se ejecutan en ISR)
// ──────────────────────────────────────────────────────────
void IRAM_ATTR post_setup_cb(spi_slave_transaction_t* trans) {
  // Llamado justo antes de que empiece la transacción
}

void IRAM_ATTR post_trans_cb(spi_slave_transaction_t* trans) {
  // Llamado justo al terminar la transacción
}

// ──────────────────────────────────────────────────────────
//  Modo esclavo con driver nativo
// ──────────────────────────────────────────────────────────
void iniciarModoEsclavo() {
  SPI.end();

  // Configurar pines manualmente para el driver nativo
  pinMode(PIN_SCK,  INPUT);
  pinMode(PIN_MOSI, INPUT);
  pinMode(PIN_MISO, OUTPUT);
  pinMode(PIN_CS,   INPUT);
  pinMode(PIN_BUS_BUSY, INPUT);

  spi_bus_config_t bus_cfg = {
    .mosi_io_num     = PIN_MOSI,
    .miso_io_num     = PIN_MISO,
    .sclk_io_num     = PIN_SCK,
    .quadwp_io_num   = -1,
    .quadhd_io_num   = -1,
    .max_transfer_sz = BUF_SIZE,
  };

  spi_slave_interface_config_t slave_cfg = {
    .spics_io_num   = PIN_CS,
    .flags          = 0,
    .queue_size     = 3,
    .mode           = 0,
    .post_setup_cb  = post_setup_cb,
    .post_trans_cb  = post_trans_cb,
  };

  // Desregistrar por si estaba inicializado antes
  spi_slave_free(VSPI_HOST);

  esp_err_t ret = spi_slave_initialize(VSPI_HOST, &bus_cfg, &slave_cfg, SPI_DMA_CH_AUTO);
  if (ret != ESP_OK) {
    Serial.printf("[ERROR] spi_slave_initialize: %s\n", esp_err_to_name(ret));
  }
}

void escucharComoEsclavo() {
  memset(rx_buf, 0, BUF_SIZE);
  memset(tx_buf, 0, BUF_SIZE);

  spi_slave_transaction_t trans = {};
  trans.length    = BUF_SIZE * 8;  // bits
  trans.tx_buffer = tx_buf;
  trans.rx_buffer = rx_buf;

  // No bloqueante: timeout de 0 ticks = solo chequea si hay algo listo
  esp_err_t ret = spi_slave_transmit(VSPI_HOST, &trans, pdMS_TO_TICKS(10));

  if (ret == ESP_OK && trans.trans_len > 0) {
    String msg = "";
    size_t bytes = trans.trans_len / 8;
    for (size_t i = 0; i < bytes; i++) {
      if (rx_buf[i] == 0) break;
      msg += (char)rx_buf[i];
    }
    if (msg.length() > 0) {
      Serial.print("[RX]: ");
      Serial.println(msg);
    }
  }
}

// ──────────────────────────────────────────────────────────
//  Modo maestro
// ──────────────────────────────────────────────────────────
void iniciarModoMaestro() {
  spi_slave_free(VSPI_HOST);
  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CS);
  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  pinMode(PIN_BUS_BUSY, OUTPUT);
  digitalWrite(PIN_BUS_BUSY, HIGH);  // Bus ocupado
}

void volverAEsclavo() {
  digitalWrite(PIN_BUS_BUSY, LOW);
  delay(2);
  SPI.end();
  iniciarModoEsclavo();
}

// ──────────────────────────────────────────────────────────
//  Arbitraje y envío
// ──────────────────────────────────────────────────────────
bool intentarEnviar(const String& msg) {
  for (int intento = 0; intento < MAX_REINTENTOS; intento++) {

    // 1. Esperar bus libre
    unsigned long t0 = millis();
    while (digitalRead(PIN_BUS_BUSY) == HIGH) {
      if (millis() - t0 > TIMEOUT_TX_MS) {
        Serial.println("[ARB] Timeout. Mensaje descartado.");
        return false;
      }
      delay(1);
    }

    // 2. Jitter aleatorio
    delay(random(0, DELAY_BASE_MS));

    // 3. Verificar de nuevo tras el jitter
    if (digitalRead(PIN_BUS_BUSY) == HIGH) {
      Serial.printf("[ARB] Colisión (intento %d), backoff...\n", intento + 1);
      delay(random(DELAY_BASE_MS, DELAY_BASE_MS * (1 << (intento + 1))));
      continue;
    }

    // 4. Tomar el bus
    iniciarModoMaestro();
    delayMicroseconds(200);

    // 5. Transacción SPI
    uint8_t buf_out[BUF_SIZE] = {0};
    uint8_t buf_in[BUF_SIZE]  = {0};
    size_t  len = min((size_t)msg.length(), (size_t)(BUF_SIZE - 1));
    memcpy(buf_out, msg.c_str(), len);

    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    delayMicroseconds(10);
    for (size_t i = 0; i < BUF_SIZE; i++) {
      buf_in[i] = SPI.transfer(buf_out[i]);
    }
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();

    // 6. Respuesta del esclavo
    String respuesta = "";
    for (size_t i = 0; i < BUF_SIZE; i++) {
      if (buf_in[i] == 0) break;
      respuesta += (char)buf_in[i];
    }
    if (respuesta.length() > 0) {
      Serial.print("[RECIBIDO]: ");
      Serial.println(respuesta);
    }

    // 7. Liberar bus y volver a esclavo
    volverAEsclavo();
    return true;
  }

  Serial.println("[ARB] Máximos reintentos. Mensaje descartado.");
  volverAEsclavo();
  return false;
}

// ──────────────────────────────────────────────────────────
//  Setup / Loop
// ──────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(34));  // Pin flotante como semilla
  delay(500);
  Serial.println("=== ESP32 SPI esclavo dinámico (core 3.x) ===");
  Serial.println("Escribe un mensaje y Enter para enviar.");
  iniciarModoEsclavo();
}

void loop() {
  // ── Leer serial ─────────────────────────────────────────
  static String bufferSerial = "";
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      if (bufferSerial.length() > 0) {
        colaEnvio = bufferSerial;
        hayMensajePendiente = true;
        bufferSerial = "";
      }
    } else {
      bufferSerial += c;
    }
  }

  // ── Enviar si hay mensaje pendiente ─────────────────────
  if (hayMensajePendiente) {
    Serial.print("[TX] Enviando: ");
    Serial.println(colaEnvio);
    intentarEnviar(colaEnvio);
    colaEnvio = "";
    hayMensajePendiente = false;
  }

  // ── Escuchar como esclavo ────────────────────────────────
  if (!hayMensajePendiente) {
    escucharComoEsclavo();
  }
}

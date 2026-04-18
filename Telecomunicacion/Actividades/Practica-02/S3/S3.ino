#include <SPI.h>
#include "driver/spi_slave.h"

// ─── Pines (ESP32-S3) ─────────────────────────────────────
// SPI2_HOST (antes HSPI) es el bus recomendado para uso general en S3
#define PIN_SCK      12
#define PIN_MISO     13
#define PIN_MOSI     11
#define PIN_CS       10
#define PIN_BUS_BUSY  9

// ─── Parámetros ───────────────────────────────────────────
#define MAX_REINTENTOS  5
#define DELAY_BASE_MS  10
#define TIMEOUT_TX_MS  200
#define BUF_SIZE       64

// ─── Buffers en DMA-capable memory ───────────────────────
static uint8_t tx_buf[BUF_SIZE];
static uint8_t rx_buf[BUF_SIZE];

bool hayMensajePendiente = false;
String colaEnvio = "";

// ──────────────────────────────────────────────────────────
//  Callbacks ISR
// ──────────────────────────────────────────────────────────
void IRAM_ATTR post_setup_cb(spi_slave_transaction_t* trans) {}
void IRAM_ATTR post_trans_cb(spi_slave_transaction_t* trans) {}

// ──────────────────────────────────────────────────────────
//  Modo esclavo
// ──────────────────────────────────────────────────────────
void iniciarModoEsclavo() {
  SPI.end();

  pinMode(PIN_SCK,      INPUT);
  pinMode(PIN_MOSI,     INPUT);
  pinMode(PIN_MISO,     OUTPUT);
  pinMode(PIN_CS,       INPUT);
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
    .spics_io_num  = PIN_CS,
    .flags         = 0,
    .queue_size    = 3,
    .mode          = 0,
    .post_setup_cb = post_setup_cb,
    .post_trans_cb = post_trans_cb,
  };

  // En S3 no existe VSPI_HOST/HSPI_HOST — se usa SPI2_HOST o SPI3_HOST
  spi_slave_free(SPI2_HOST);

  esp_err_t ret = spi_slave_initialize(SPI2_HOST, &bus_cfg, &slave_cfg, SPI_DMA_CH_AUTO);
  if (ret != ESP_OK) {
    Serial.printf("[ERROR] spi_slave_initialize: %s\n", esp_err_to_name(ret));
  }
}

void escucharComoEsclavo() {
  memset(rx_buf, 0, BUF_SIZE);
  memset(tx_buf, 0, BUF_SIZE);

  spi_slave_transaction_t trans = {};
  trans.length    = BUF_SIZE * 8;
  trans.tx_buffer = tx_buf;
  trans.rx_buffer = rx_buf;

  esp_err_t ret = spi_slave_transmit(SPI2_HOST, &trans, pdMS_TO_TICKS(10));

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
  spi_slave_free(SPI2_HOST);
  // En S3 se especifican los pines explícitamente en begin()
  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CS);
  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  pinMode(PIN_BUS_BUSY, OUTPUT);
  digitalWrite(PIN_BUS_BUSY, HIGH);
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

    // 3. Verificar tras el jitter
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
      respuesta += (char)respuesta[i];
    }
    if (respuesta.length() > 0) {
      Serial.print("[RECIBIDO]: ");
      Serial.println(respuesta);
    }

    // 7. Liberar bus
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
  randomSeed(analogRead(1));  // En S3 evitar GPIO 0 como pin flotante
  delay(500);
  Serial.println("=== ESP32-S3 SPI esclavo dinámico ===");
  Serial.println("Escribe un mensaje y Enter para enviar.");
  iniciarModoEsclavo();
}

void loop() {
  static String bufferSerial = "";

  // ── Leer serial ─────────────────────────────────────────
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

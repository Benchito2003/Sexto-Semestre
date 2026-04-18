#include <SPI.h>
#include "driver/spi_slave.h"

#define MOSI_PIN 13
#define MISO_PIN 11
#define SCLK_PIN 12
#define CS_PIN   10

static const int BUFFER_SIZE = 64;
char rx_buf[BUFFER_SIZE];
char tx_buf[BUFFER_SIZE];

spi_slave_transaction_t t;

void setup() {
  Serial.begin(115200);

  spi_bus_config_t buscfg = {
    .mosi_io_num = MOSI_PIN,
    .miso_io_num = MISO_PIN,
    .sclk_io_num = SCLK_PIN,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
  };

  // ✅ Orden corregido
  spi_slave_interface_config_t slvcfg = {
    .spics_io_num = CS_PIN,
    .flags = 0,
    .queue_size = 3,
    .mode = 0,
    .post_setup_cb = NULL,
    .post_trans_cb = NULL,
  };

  esp_err_t ret = spi_slave_initialize(SPI2_HOST, &buscfg, &slvcfg, SPI_DMA_CH_AUTO);
  if (ret != ESP_OK) {
    Serial.println("Error inicializando SPI Slave: " + String(esp_err_to_name(ret)));
    return;
  }

  memset(rx_buf, 0, BUFFER_SIZE);
  snprintf(tx_buf, BUFFER_SIZE, "S3-LISTO");

  t.length = BUFFER_SIZE * 8;
  t.tx_buffer = tx_buf;
  t.rx_buffer = rx_buf;

  spi_slave_queue_trans(SPI2_HOST, &t, portMAX_DELAY);
  Serial.println("ESP32-S3 SPI Slave Listo. Esperando datos...");
}

void loop() {
  spi_slave_transaction_t *ret_trans;

  if (spi_slave_get_trans_result(SPI2_HOST, &ret_trans, 0) == ESP_OK) {
    String msg = String(rx_buf).substring(0, ret_trans->trans_len / 8);
    msg.trim();

    if (msg.length() > 0) {
      Serial.println("[RX SPI recibido del Master]: " + msg);

      String respuesta = "ACK:" + msg;
      memset(tx_buf, 0, BUFFER_SIZE);
      respuesta.toCharArray(tx_buf, BUFFER_SIZE);
      Serial.println("[TX SPI respuesta preparada]: " + respuesta);
    }

    memset(rx_buf, 0, BUFFER_SIZE);
    t.length = BUFFER_SIZE * 8;
    t.tx_buffer = tx_buf;
    t.rx_buffer = rx_buf;
    spi_slave_queue_trans(SPI2_HOST, &t, portMAX_DELAY);
  }
}

#include <Arduino.h>
#include <driver/spi_slave.h>

#define SPI_SLAVE_MISO 19
#define SPI_SLAVE_MOSI 23
#define SPI_SLAVE_SCK  18
#define SPI_SLAVE_CS   5

const int bufferSize = 32;

// En ESP-IDF, los buffers DMA deben estar alineados a 32 bits
WORD_ALIGNED_ATTR char tx_buf[bufferSize];
WORD_ALIGNED_ATTR char rx_buf[bufferSize];

void setup() {
  Serial.begin(115200);

  // Configuración del bus
  spi_bus_config_t buscfg = {};
  buscfg.mosi_io_num = SPI_SLAVE_MOSI;
  buscfg.miso_io_num = SPI_SLAVE_MISO;
  buscfg.sclk_io_num = SPI_SLAVE_SCK;
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;

  // Configuración de la interfaz
  spi_slave_interface_config_t slvcfg = {};
  slvcfg.spics_io_num = SPI_SLAVE_CS;
  slvcfg.flags = 0;
  slvcfg.queue_size = 1;
  slvcfg.mode = 0;

  spi_slave_initialize(VSPI_HOST, &buscfg, &slvcfg, SPI_DMA_DISABLED);
  
  Serial.println("--- Esclavo SPI Listo ---");
  Serial.println("Escribe un mensaje y presiona Enter...");
}

void loop() {
  memset(tx_buf, 0, bufferSize);
  memset(rx_buf, 0, bufferSize);

  // 1. Verificamos si escribiste algo en el Monitor Serie del Esclavo
  if (Serial.available()) {
    int len = Serial.readBytesUntil('\n', tx_buf, bufferSize - 1);
    tx_buf[len] = '\0';
    Serial.print("Tú (Esclavo): ");
    Serial.println(tx_buf);
  }

  // 2. Preparamos la transacción que tomará el Maestro
  spi_slave_transaction_t t;
  memset(&t, 0, sizeof(t));
  t.length = bufferSize * 8; // La longitud se define en bits
  t.tx_buffer = tx_buf;
  t.rx_buffer = rx_buf;

  // Esta función pausa el bucle hasta que el Maestro ejecute su polling de 100ms
  esp_err_t ret = spi_slave_transmit(VSPI_HOST, &t, portMAX_DELAY);
  
  // 3. Verificamos si el Maestro mandó algo útil
  if (ret == ESP_OK && rx_buf[0] != '\0' && rx_buf[0] != 0xFF) {
    Serial.print("Maestro dice: ");
    Serial.println(rx_buf);
  }
}

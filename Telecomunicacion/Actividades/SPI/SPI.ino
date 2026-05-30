#include <Arduino.h>
#include <SPI.h>
#include "driver/spi_slave.h"

#define SS 5
#define REQ 4
WORD_ALIGNED_ATTR uint8_t b[64];
spi_slave_transaction_t t;

void ini() {
  esp_log_level_set("spi_slave", ESP_LOG_NONE);
  spi_slave_free(VSPI_HOST); spi_bus_free(VSPI_HOST);
  spi_bus_config_t c = {.mosi_io_num=23, .miso_io_num=19, .sclk_io_num=18, .quadwp_io_num=-1, .quadhd_io_num=-1};
  spi_slave_interface_config_t s = {.spics_io_num=SS, .queue_size=1, .mode=0};
  spi_slave_initialize(VSPI_HOST, &c, &s, 2);
  memset(b, 0, 64); memset(&t, 0, sizeof(t));
  t.length = 8; t.rx_buffer = b; 
  spi_slave_queue_trans(VSPI_HOST, &t, portMAX_DELAY);
}

void setup() {
  Serial.begin(115200);
  pinMode(REQ, INPUT_PULLUP); pinMode(SS, INPUT_PULLUP);
  ini();
}

void loop() {
  spi_slave_transaction_t* r;
  if (spi_slave_get_trans_result(VSPI_HOST, &r, 0) == ESP_OK) {
    if (b[0]) Serial.print((char)b[0]);
    memset(b, 0, 64); 
    spi_slave_queue_trans(VSPI_HOST, &t, portMAX_DELAY);
  }

  if (Serial.available() && digitalRead(REQ)) {
    char c = Serial.read();
    pinMode(REQ, OUTPUT); digitalWrite(REQ, 0); 
    
    ini(); // Mata esclavo
    
    SPI.begin(18, 19, 23, SS);
    pinMode(SS, OUTPUT); digitalWrite(SS, 0);
    SPI.beginTransaction(SPISettings(500000, 1, SPI_MODE0)); 
    SPI.endTransaction();
    digitalWrite(SS, 1);
    
    delay(5); 
    SPI.end();
    pinMode(REQ, INPUT_PULLUP);
    ini();
  }
}

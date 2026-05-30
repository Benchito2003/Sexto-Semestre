#include <Wire.h>
#define ID 1     // ESP1 = 1   |   ESP2 = 0
#define SDA_PIN 21
#define SCL_PIN 22
#define SLAVE_ADDR 0x09
char c;
volatile char out = 0;
void rx(int n)
{
  while (Wire.available())
  {
    char x = Wire.read();
    Serial.write(x);
  }
}
void rq()HHH
{
  Wire.write(out);
  out = 0;
}
void setup()
{
  Serial.begin(115200);
  if (ID == 1)
  {
    Wire.begin(SDA_PIN, SCL_PIN, 100000);
  }
  else
  {
    Wire.begin(SLAVE_ADDR, SDA_PIN, SCL_PIN, 100000);
    Wire.onReceive(rx);
    Wire.onRequest(rq);
  }
  Serial.println("LISTO");
}
void loop()
{
  if (ID == 1)
  {
    if (Serial.available())
    {
      c = Serial.read();
      Serial.write(c);   
      Wire.beginTransmission(SLAVE_ADDR);
      Wire.write(c);
      Wire.endTransmission();
    }
    Wire.requestFrom(SLAVE_ADDR, 1);
    if (Wire.available())
    {
      c = Wire.read();
      if (c != 0)
        Serial.write(c);
    }
    delay(10);
  }
  else
  {
    if (Serial.available())
    {
      out = Serial.read();
      Serial.write(out);   
    }
    delay(1);
  }
}

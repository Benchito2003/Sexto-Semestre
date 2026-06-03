## Tema 11: RADIOFRECUENCIA Y MODULACIÓN
https://youtu.be/-pDbamqOAyw?si=_I0HpDMc9dQKJfo5

La **Radiofrecuencia** se refiere a la porción del espectro electromagnético utilizada para transmitir datos a través del aire. En biomédica, esto es la base de la telemetría cardíaca o la comunicación de implantes.

- **Espectro Electromagnético:** Rango de frecuencias de radiación. La RF típicamente abarca de $3kHz$ a  $300GHz$.
- **Onda Portadora (Carrier):** Una onda senoidal de alta frecuencia que "transporta" la información. Su ecuación básica es: $$v(t) = A \sin(2\pi ft + \phi)$$
- **Ancho de Banda (Bandwidth):** La diferencia entre la frecuencia superior e inferior de una señal. A mayor ancho de banda, mayor velocidad de transmisión.
La modulación es el proceso de variar una propiedad de la portadora (amplitud, frecuencia o fase) en función de una señal de datos. Sin ella, no podríamos distinguir entre diferentes transmisiones ni transmitir a largas distancias con antenas de tamaño razonable.

- **ASK (Amplitude Shift Keying):** Varía la amplitud. Es sencilla pero muy sensible al ruido (común en interferencias hospitalarias).
- **FSK (Frequency Shift Keying):** Varía la frecuencia. Es más robusta ante el ruido. El NRF24L01 utiliza una variante llamada **GFSK** (Gaussian FSK), que suaviza las transiciones de frecuencia para ocupar menos ancho de banda.
- **PSK (Phase Shift Keying):** Varía la fase de la onda. Muy eficiente para altas tasas de datos.
### El Módulo NRF24L01: El estándar para Proyectos Biomédicos

Este transceptor es extremadamente popular en biomédica por su bajo consumo de energía (ideal para sensores de pulso o temperatura de batería corta) y su operación en la banda libre de **2.4 GHz (ISM)**.

  

#### Datos Técnicos y Teóricos Críticos

|**Característica**|**Detalle Técnico**|
|---|---|
|**Banda de Frecuencia**|2.400 a 2.525 GHz|
|**Modulación**|GFSK (Gaussian Frequency Shift Keying)|
|**Velocidad de Datos**|250 kbps, 1 Mbps o 2 Mbps|
|**Voltaje de Operación**|1.9 a 3.6 V (¡Cuidado! Sus pines son tolerantes a 5V, pero el VCC no)|
|**Consumo en TX**|~11.3 mA a 0 dBm de salida|
|**Canales**|125 canales seleccionables (permite redes de muchos sensores)|


#### Protocolo ShockBurst™ Mejorado

A diferencia de otros módulos, el NRF24L01 maneja automáticamente el empaquetado de datos, el **CRC** (verificación de errores) y el **Auto-Acknowledgement** (confirmación de recepción), liberando al microcontrolador de estas tareas pesadas.

### Comunicación con el Microcontrolador: Protocolo SPI

Para que el ingeniero biomédico pueda configurar el NRF24L01, debe dominar el protocolo **SPI (Serial Peripheral Interface)**. Es una comunicación síncrona de tipo maestro-esclavo.

  

#### Pines Críticos del NRF24L01 para SPI:

1. **MOSI (Master Out Slave In):** Datos del microcontrolador al NRF.
2. **MISO (Master In Slave Out):** Datos del NRF al microcontrolador.
3. **SCK (Serial Clock):** El pulso que sincroniza la lectura de bits.
4. **CSN (Chip Select Not):** Se pone en nivel BAJO para avisarle al NRF que vamos a hablar con él.
5. **CE (Chip Enable):** Pin específico del NRF para activar el modo de transmisión o escucha (TX/RX).
    

> **Nota para los alumnos:** En dispositivos médicos, el SPI es preferido sobre I2C por su mayor velocidad, lo cual es crítico cuando se transmiten señales en tiempo real como un **ECG (Electrocardiograma)** que requiere alta tasa de muestreo.

### CODIGO PARA COMUNICACIÓN DE RADIO POR ESP32 Y NRF24L01

#### **EMISOR**
```c
import machine, time, struct  
from machine import Pin, SPI  
from nrf24l01 import NRF24L01  
  
# Configuración de pines SPI para ESP32  
spi = SPI(1, baudrate=4000000, sck=Pin(14), mosi=Pin(13), miso=Pin(12))  
  
# Pines CE y CSN (Pin 17 y Pin 5)  
nrf = NRF24L01(spi, Pin(5), Pin(17), payload_size=8)  
  
# Dirección de red (5 bytes en hexadecimal)  
DIRECCION = b"\x11\x22\x33\x44\x00"  
  
nrf.open_tx_pipe(DIRECCION)  
nrf.stop_listening()  
  
dato = 0.0  
  
print("Transmisor listo...")  
  
while True:  
try:  
# Convertimos el número a formato binario (4 bytes)  
paquete = struct.pack("f", dato)  
nrf.send(paquete)  
print("Enviado:", dato)  
dato += 1.0  
except OSError:  
print("Error: Receptor no encontrado")  
  
time.sleep(2)

```
  

#### **RECEPTOR**

```c
import machine, time, struct  
from machine import Pin, SPI  
from nrf24l01 import NRF24L01  
  
# Configuración de pines SPI para ESP32  
spi = SPI(1, baudrate=4000000, sck=Pin(14), mosi=Pin(13), miso=Pin(12))  
  
# Pines CE y CSN (Pin 17 y Pin 5)  
nrf = NRF24L01(spi, Pin(5), Pin(17), payload_size=8)  
  
# Dirección de red (Debe ser idéntica a la del emisor)  
DIRECCION = b"\x11\x22\x33\x44\x00"  
  
nrf.open_rx_pipe(1, DIRECCION)  
nrf.start_listening()  
  
print("Receptor esperando datos...")  
  
while True:  
if nrf.any():  
# Recibimos el paquete binario  
paquete = nrf.recv()  
# Lo convertimos de vuelta a número decimal (float)  
dato_recibido = struct.unpack("f", paquete)[0]  
print("Recibido:", dato_recibido)  
  
time.sleep_ms(100)
```

## Tema 12: BLUETOOTH Y REDES HOSPITALARIAS
https://youtu.be/wAW8rG9tKJI?si=7VkIThejYcJ-cU3P
### 1. Bluetooth Low Energy (BLE) en el Entorno Biomédico

A diferencia del Bluetooth clásico (usado para audio), el **BLE (Bluetooth 4.0+)** fue diseñado para dispositivos médicos que necesitan funcionar durante meses o años con una sola batería de botón.

#### Conceptos Teóricos Clave

- **Banda ISM 2.4 GHz:** Al igual que el NRF24L01, opera aquí, pero utiliza **Adaptive Frequency Hopping (AFH)**. Esto es vital en hospitales para saltar automáticamente de frecuencia y evitar la interferencia con el Wi-Fi de las máquinas de rayos X o monitores.
- **Arquitectura GATT (Generic Attribute Profile):** Es la forma en que el Bluetooth organiza la información médica. Se divide en:
    - **Servicios:** (Ej. Servicio de Frecuencia Cardíaca).
    - **Características:** (Ej. El valor exacto de las pulsaciones por minuto).
- **Beaconing:** En hospitales, los dispositivos BLE se usan para "RTLS" (Sistemas de Localización en Tiempo Real) para rastrear dónde está una cama eléctrica o un ventilador pulmonar.
    

### 2. Redes Hospitalarias y Topologías

En una Experiencia Educativa de telecomunicaciones, es vital entender cómo se agrupan estos sensores.

#### Tipos de Redes según Cobertura

1. **WBAN (Wireless Body Area Network):** Sensores colocados en el cuerpo del paciente (ECG, Oxímetro) que se comunican con un concentrador (monitor de cabecera).
2. **WPAN (Wireless Personal Area Network):** El monitor de cabecera enviando datos a la tableta del médico.
3. **WLAN (Wireless Local Area Network):** La infraestructura Wi-Fi del hospital que conecta todo con el expediente clínico electrónico.

#### El Desafío de la Interoperabilidad

En un hospital hay equipos de distintas marcas. Por eso se utiliza el estándar **IEEE 11073**, que define cómo deben comunicarse los dispositivos médicos personales para que un monitor marca _X_ entienda a un sensor marca _Y_.

### 3. Bluetooth vs. NRF24L01: Comparativa Técnica

|**Característica**|**NRF24L01 (RF Privada)**|**Bluetooth Low Energy (BLE)**|
|---|---|---|
|**Protocolo de Red**|Propietario (ShockBurst)|Estándar Global (SIG)|
|**Seguridad**|Básica (Cifrado manual)|Avanzada (AES-128 integrado)|
|**Conectividad**|Solo con otros NRF24|Smartphones, Tablets, Laptops|
|**Topología**|Estrella / Árbol|Estrella / Mesh (Malla)|
|**Uso Biomédico**|Prototipos / Telemetría simple|Dispositivos médicos certificados|

### CODIGO PARA COMUNICACIÓN ENTRE DISPOSITIVO MÓVIL Y ESP32 POR BLUETOOTH
```c
#include "BluetoothSerial.h"                                                                                                                                     // Comprobar si el Bluetooth está habilitado correctamente                                                                           #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)                                 #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it                                 #endif    

                                                                                                                                                                            BluetoothSerial SerialBT;void setup() {                                                                                            Serial.begin(115200);

  // Nombre del dispositivo que aparecerá en tu celular

  // Podrías nombrarlo "Monitor_Medico_Seguro"

  SerialBT.begin("ESP32_Paciente_01"); 

  Serial.println("El dispositivo está listo para emparejar.");

  Serial.println("Busca 'ESP32_Paciente_01' en tu celular.");

}

void loop() {

  // Enviar datos del Celular -> Monitor Serial del PC

  if (SerialBT.available()) {

    Serial.write(SerialBT.read());

  }

  // Enviar datos del PC (Monitor Serial) -> Celular

  if (Serial.available()) {

    SerialBT.write(Serial.read());

  }

  delay(20);

}

```

La conexión requiere de un software (aplicación) bajo el nombre "Serial Bluetooth Terminal" en el dispositivo móvil

## Tema 13: APLICACIÓN DE PROTOCOLOS Y DISPOSITIVOS DE COMUNICACIÓN
https://youtu.be/IQ22Nme9t0M?si=zje5k2-grrMJX2WW

### Teoría: El Modelo OSI en la Telemetría Biomédica

Para que un dato del sensor **MAX30102** llegue a una base de datos web, debe atravesar diferentes capas. Es vital que los alumnos identifiquen qué protocolo actúa en cada etapa del proceso:

  

### Mapeo de Capas en el Proyecto
- **Capa 7 (Aplicación):** **HTTP/HTTPS**. Es el protocolo que define cómo se envían los datos del pulso al servidor web (ej. mediante un método `POST`).
- **Capa 4 (Transporte):** **TCP**. Se encarga de que los paquetes del pulso cardíaco lleguen completos y en orden. Si un paquete se pierde, TCP solicita el reenvío (vital para diagnósticos médicos).
- **Capa 3 (Red):** **IP (Internet Protocol)**. Provee el direccionamiento lógico para que el ESP32 encuentre la ruta hacia el servidor en la web.
- **Capa 2 (Enlace de Datos):** Aquí ocurre la magia del hardware.
    - **WiFi (802.11):** Entre el ESP32 y el Router.
    - **ShockBurst:** Entre el NRF24L01 (Nodo sensor) y el ESP32 (Gateway).
- **Capa 1 (Física):** Las señales eléctricas en los pines **I2C** del sensor, el bus **SPI** del radio y las ondas de **2.4 GHz** en el aire.



### Flujo del Sistema de Comunicación

El sistema se divide en tres nodos principales para demostrar la aplicación de protocolos en una red jerárquica:

#### Nodo A: Adquisición (Sensor + NRF24L01)

- **Sensor MAX30102:** Utiliza el protocolo **I2C** (Inter-Integrated Circuit). Mide la frecuencia cardíaca mediante fotopletismografía.
- **Transmisión Local:** Envía los datos al Nodo B usando el protocolo propietario de los NRF24L01. Este es un entorno de bajo consumo, simulando un sensor que el paciente lleva puesto.

#### Nodo B: Gateway (NRF24L01 + ESP32)

- **Traducción de Protocolos:** Este nodo actúa como "traductor". Recibe datos por **SPI**, los procesa y los encapsula en un stack **TCP/IP** para enviarlos por Wi-Fi.
    
- **Petición Web:** Genera una solicitud **HTTP** hacia una página web o API.
    



### Implementación: Del Bit a la Base de Datos

#### Conexión I2C y SPI

Es fundamental que los estudiantes diferencien estos protocolos serie:

1. **I2C (MAX30102):** Usa solo 2 hilos (SDA, SCL), ideal para distancias cortas entre sensor y MCU.
2. **SPI (NRF24L01):** Es mucho más rápido, lo que permite que el ESP32 gestione el radio y el Wi-Fi casi simultáneamente.
    

### Envío a la Web (Capa de Aplicación)

El ESP32 debe estructurar una petición que el servidor web entienda. Un ejemplo de la carga útil sería:
```
POST /api/pulso HTTP/1.1 Host: hospital-digital.com Content-Type: application/json 
{  "paciente_id": "001",  "bpm": 75,  "spo2": 98 }
```

### Análisis con Wireshark: Identificación de Protocolos

Una vez que el sistema está transmitiendo, los alumnos utilizarán **Wireshark** para realizar una "autopsia" de los paquetes de datos.

#### Qué buscar en Wireshark:

1. **Handshake TCP:** Filtrar por `tcp.flags.syn == 1` para ver cómo el ESP32 "saluda" al servidor antes de enviar el pulso.
2. **Protocolo HTTP:** Usar el filtro `http`. Aquí verán el envío de datos en texto plano (o cifrado si usan HTTPS). Podrán observar la dirección IP de origen (ESP32) y destino (Servidor).
3. **Análisis de Tiempos:** Evaluar el "Delta time" para determinar la latencia. En aplicaciones críticas como la monitorización cardíaca, una latencia alta puede ser peligrosa.
### Resumen Pedagógico para la Clase

> "Como ingenieros biomédicos, nuestra responsabilidad es asegurar la **integridad del dato**. Si Wireshark nos muestra muchos reenvíos TCP, sabemos que hay interferencia en la red hospitalaria (Capa 1 o 2). Si el servidor no recibe nada pero el WiFi está bien, el problema está en nuestro formato HTTP (Capa 7)."

¿Te gustaría que te proporcione el **archivo de configuración del servidor (PHP o Python)** y la estructura de la **base de datos MySQL** para que tus alumnos tengan un lugar real a donde enviar la información?

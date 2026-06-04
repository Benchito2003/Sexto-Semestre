## Hall
### ¿Dónde está? 
Está **integrado en el estator del motor**, específicamente en la placa de circuito impreso (PCB) circular verde que rodea al eje.
- **Ubicación precisa:** Si miras el borde interior de la placa verde (el círculo que rodea el rodamiento central), verás tres pequeñas protuberancias o componentes encapsulados en plástico negro, dispuestos simétricamente a 120 grados eléctricos de separación. Esos son los sensores Hall. Están ahí para detectar los campos magnéticos de los imanes permanentes que están pegados en la cara interna del rotor (la parte metálica móvil que gira sobre ellos).
### ¿Comunicación? 
Tiene una **comunicación digital de estado lógico (Open-Collector / Digital I/O)**.

- **No es un bus de datos:** No "habla" por protocolos como I2C, SPI o UART.
    
- **Funcionamiento:** Cada sensor Hall es un interruptor magnético. Cuando detecta el polo norte del imán, su salida cae a `0` (GND). Cuando detecta el polo sur o está en campo neutro, su salida sube a `1` (VCC).
    
- **Cómo lo lee el micro:** El procesador (en este caso el _Artery_ original y pronto tu _ESP32-S3_) simplemente monitorea los niveles de voltaje de los tres pines de señal (A, B y C). Al cambiar los estados de estos 3 pines, el micro sabe exactamente en qué posición está el rotor y a qué velocidad está girando, basándose en la secuencia de cambios (ej. `001 -> 011 -> 010...`).
### ¿Voltaje?
Usa **5V DC**.

- **¿Por qué sabemos esto?** Los sensores de efecto Hall industriales (como los de la serie SS41 o similares que se usan en BLDC) están diseñados para operar en un rango robusto de **4.5V a 24V**.
    
- **Confirmación en tu placa:** En la foto de la placa azul (donde está el chip _Artery_ y el _EG2136_), verás cerca del conector de 9 pines un regulador de voltaje o un divisor que entrega exactamente **+5V**.
    
- **Importante para tu diseño:** Como el ESP32-S3 funciona a **3.3V**, cuando conectes las señales A, B y C a los pines GPIO de tu micro, **tienes que usar el divisor de voltaje** (dos resistencias por cada señal) para bajar esos 5V de pico a 3.3V. Si conectas 5V directo a un pin del ESP32, corres un riesgo muy alto de dañar ese pin del microcontrolador.

## Alpha
### ¿Se puede?
### ¿Que pin?
### ¿Qué comunicación?

## Torque
### ¿Pin placa?
### ¿Qué voltaje?
### ¿Qué comunicación?
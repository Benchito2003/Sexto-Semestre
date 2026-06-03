# Unidad 3
## Tema 8: ARQUITECTURAS DE RED Y SU APLICACIÓN EN TELEMEDICINA
### Modelo OSI
Modelo OSI: https://youtu.be/ODY4q4_3Acc?si=OWiDkhg-oGMaPjQv

  

El **Modelo OSI** (Open Systems Interconnection) es el mapa universal para entender cómo viajan los datos entre dos dispositivos. Imagina que es el "manual de reglas" que permite que un sensor médico, una computadora y un servidor de hospital hablen el mismo idioma, sin importar quién los fabricó.

Se divide en **7 capas**, donde cada una tiene una misión específica. Los datos bajan desde la capa 7 (usuario) hasta la 1 (cable) en el emisor, y hacen el recorrido inverso en el receptor.

### Las 7 Capas del Modelo OSI

|**Capa**|**Nombre**|**Función Principal**|**Protocolos / Ejemplos**|
|---|---|---|---|
|**7**|**Aplicación**|Interfaz directa con el usuario o software.|HTTP, FTP, **DICOM** (Imágenes médicas).|
|**6**|**Presentación**|Traduce, cifra y comprime los datos (el "traductor").|SSL/TLS, ASCII, JPG, MP4.|
|**5**|**Sesión**|Mantiene la conexión abierta y la sincroniza.|NetBIOS, RPC, SQL.|
|**4**|**Transporte**|Divide los datos en segmentos y garantiza la entrega.|**TCP** (seguro), **UDP** (rápido).|
|**3**|**Red**|Decide la ruta que seguirán los datos (Direccionamiento).|**IP (IPv4/IPv6)**, ICMP (Ping), Routers.|
|**2**|**Enlace de Datos**|Transferencia confiable entre dos nodos (Tramas).|**Ethernet**, Wi-Fi, Switches, MAC Address.|
|**1**|**Física**|Transmisión de bits por el medio físico (Voltajes).|**Fibra óptica, Par trenzado, Coaxial, USB.**|
### Relación Técnica entre las Capas

Para que un dato baje de una capa a otra, ocurre un proceso llamado **Encapsulamiento**:

- En la **Capa 4**, el mensaje se convierte en un **Segmento**.
- En la **Capa 3**, se le añade la dirección IP y se vuelve un **Paquete**.
- En la **Capa 2**, se le añade la dirección MAC y se vuelve una **Trama**.
- En la **Capa 1**, la trama se convierte en **Bits** (pulsos eléctricos o de luz).
    

### El Modelo OSI en la Ingeniería Biomédica

Entender el modelo OSI es fundamental para un Ingeniero Biomédico porque la mayoría de los fallos en equipos médicos interconectados no son del equipo en sí, sino de la comunicación entre capas.

**Ejemplo de flujo en un entorno hospitalario:**

Cuando un **monitor de signos vitales** envía la frecuencia cardíaca de un paciente a la central de enfermería:

1. **Capa Física:** Los bits viajan por un cable de **Par Trenzado (Cat 6A)** o por el aire vía **Wi-Fi**.    
2. **Capas de Red y Transporte:** El protocolo **IP** direcciona el dato al servidor correcto y el protocolo **TCP** asegura que no se pierda ningún latido en el camino.
3. **Capa de Aplicación:** El software de la central de enfermería recibe el dato y muestra la onda del ECG en pantalla.
    

**La importancia del diagnóstico:**

Si el monitor no conecta, el ingeniero biomédico debe hacer un "troubleshooting" siguiendo el modelo OSI:

- ¿Está bien el cable? (**Capa 1**)
- ¿El Switch reconoce el equipo? (**Capa 2**)
- ¿Tiene asignada una dirección IP correcta? (**Capa 3**)
- ¿El software del fabricante está escuchando el puerto correcto? (**Capa 7**)
    

> **Nota Crítica:** En biomedicina, un error en la **Capa 4 (Transporte)** al elegir UDP en lugar de TCP para datos críticos podría causar que una alarma de paro cardíaco no llegue a tiempo porque "se perdió el paquete en la red".

![[Pasted image 20260602160411.png]]

## Tema 9:ARQUITECTURA TCP/IP y DIRECCIONAMIENTO
![[Pasted image 20260602160441.png]]

Para un ingeniero biomédico, entender **TCP/IP** es vital: es el lenguaje que permite que un tomógrafo en el sótano envíe una imagen de 500MB a la computadora de un médico en el quinto piso sin errores.

El modelo **TCP/IP** (Transmission Control Protocol / Internet Protocol) es un conjunto de reglas que dividen la información en paquetes, los envían por el medio físico (que ya vimos) y los reensamblan en el destino.


### Las 4 Capas del Modelo TCP/IP

Imagina que estás enviando un electrocardiograma (ECG) desde un monitor a una base de datos. Los datos bajan por estas capas:

1. **Capa de Aplicación:** Donde interactúa el software (ej. protocolos de imagen médica como **DICOM** o mensajería **HL7**). Es lo que el usuario ve.
2. **Capa de Transporte (TCP/UDP):** Aquí se decide cómo viajarán los datos.
    - **TCP:** Es "orientado a conexión". Verifica que cada paquete llegue. Si uno se pierde, lo pide de nuevo. (Ideal para historias clínicas).
    - **UDP:** Envía datos sin verificar. Es más rápido pero menos confiable. (Ideal para streaming de video en una cirugía en vivo).
3. **Capa de Internet (IP):** Es el sistema de "correos". Aquí se le pone la dirección de origen y destino a cada paquete. El dispositivo clave aquí es el **Router**.
4. **Capa de Acceso a Red:** Es la interfaz con el cable (el par trenzado, fibra o coaxial). Define cómo los bits se convierten en señales eléctricas o de luz.

Cada equipo médico en la red necesita una dirección única para ser localizado. Actualmente conviven dos versiones:

### IPv4 (El estándar actual)

Se escribe como cuatro números del 0 al 255, separados por puntos (ej. `192.168.1.50`).

- **Estructura:** Son 32 bits en total.
- **Partes de la IP:** Se divide en **Red** (identifica el hospital o departamento) y **Host** (identifica el equipo específico, como la "Bomba de infusión 4").
- **Máscara de Subred:** Le dice a la computadora qué parte de la dirección es la red y cuál es el equipo. (Ej. `255.255.255.0`).

  

### IPv6 (El futuro)

Debido a que hay miles de millones de dispositivos (IoT médico), las direcciones IPv4 se acabaron. IPv6 usa 128 bits y se escribe en hexadecimal (ej. `2001:0db8:85a3...`).



### Conceptos Clave de Red en Hospitales

Para que los alumnos conecten esto con su carrera, deben dominar estos tres términos:

1. **Dirección MAC (Dirección Física):** Es la "matrícula" única que el fabricante le pone a la tarjeta de red de un equipo médico. No cambia nunca.
2. **Puerta de Enlace (Default Gateway):** Es la dirección del router que permite que el equipo médico salga de su red local hacia internet o hacia otros departamentos.
3. **DHCP vs. IP Estática:**
    - **Estática:** Se configura manualmente. **Obligatoria para servidores de imágenes o impresoras médicas**, para que siempre estén en la misma dirección.
    - **DHCP:** El servidor asigna una IP automática. Útil para tablets de enfermería que se mueven por el hospital.


### Ejercicio de Aplicación Técnica

**Situación:** Tienes un equipo de Rayos X con la IP `192.168.10.15` y una máscara `255.255.255.0`. Quieres enviar una placa a un servidor con la IP `192.168.20.5`.

**Preguntas para los alumnos:**

1. ¿Están en la misma subred? (Pista: Mira el tercer octeto).
2. ¿Qué dispositivo de red es necesario para que los datos lleguen del equipo de Rayos X al servidor? (Respuesta: Un **Router**).
3. Si la imagen debe llegar completa y sin un solo pixel alterado, ¿qué protocolo de transporte usarías, **TCP** o **UDP**?

## Tema 10: WIFI Y TRANSMISIÓN DE INFORMACIÓN BIOMÉDICA

El uso de **Wi-Fi** en ingeniería biomédica es fascinante pero delicado. A diferencia de los cables que vimos antes, aquí la señal viaja por el aire usando ondas de radio (RF), lo que introduce variables como interferencias por muros, otros equipos médicos y riesgos de seguridad.

Para un ingeniero biomédico, el Wi-Fi no es solo "internet inalámbrico", es un **medio compartido** que debe gestionarse bajo estándares estrictos.

### Estándares y Frecuencias (IEEE 802.11)

El Wi-Fi opera principalmente en dos bandas de frecuencia, y la elección de una u otra puede afectar la estabilidad de un monitor de signos vitales:

- **Banda de 2.4 GHz:** Tiene mayor alcance y atraviesa mejor las paredes de los hospitales. **Problema:** Está saturada. Microondas, Bluetooth y teléfonos viejos interfieren aquí.
- **Banda de 5 GHz:** Es mucho más rápida y tiene menos interferencia. **Problema:** Su alcance es menor y los muros de plomo (comunes en salas de rayos X) bloquean la señal casi por completo.
- **Banda de 6 GHz (Wi-Fi 6E/7):** La frontera actual. Ofrece canales ultra limpios, ideales para cirugía robótica o streaming de video médico en 4K.

### 2. Transmisión de Contenido Biomédico: El reto de la Latencia

Cuando transmitimos datos médicos por Wi-Fi, los clasificamos por su criticidad:

#### A. Datos Críticos (Tiempo Real)

- **Ejemplos:** Telemetría cardíaca, alarmas de respiradores, video de cirugía remota.
- **Requisito:** Baja **latencia** (retraso) y bajo **jitter** (variación del retraso).
- **Protocolo:** Aquí se suele usar **UDP** dentro de la capa de transporte, porque si un paquete de video se pierde, es mejor seguir con el siguiente que detener la transmisión para pedir el anterior (como haría TCP).

#### B. Datos No Críticos (Asíncronos)

- **Ejemplos:** Envío de una Historia Clínica Electrónica o una receta digital.
- **Requisito:** Integridad total.
- **Protocolo:** Se usa **TCP** para asegurar que no falte ni una letra del diagnóstico.
    

### 3. Desafíos Técnicos en el Hospital

Para que tus alumnos analicen la viabilidad del Wi-Fi, deben considerar estos tres factores:

1. **Atenuación por Blindaje:** Los hospitales están llenos de jaulas de Faraday (salas de MRI) y paredes con barita o plomo. Un diseño de red Wi-Fi biomédica requiere un "Site Survey" para ubicar los Puntos de Acceso (AP) estratégicamente.
2. **Densidad de Dispositivos:** En una UCI puede haber 20 bombas de infusión, 10 monitores y 5 tablets, todos conectados al mismo AP. Si el ancho de banda se agota, las alarmas podrían llegar tarde.
3. **Seguridad (WPA3):** Los datos biomédicos son privados. El Wi-Fi debe estar cifrado para evitar el "eavesdropping" (escucha ilegal) de señales de pacientes.
    

### 4. Ejercicio de Análisis: Wi-Fi en la Sala de Operaciones

**Planteamiento:**Se desea implementar un sistema de **anestesia digital** que envía los niveles de gas del paciente a una tablet vía Wi-Fi. El hospital tiene muros gruesos y muchos equipos de electrocauterio funcionando.

**Preguntas para los alumnos:**

1. **¿Qué banda usarías?** Si eliges 2.4 GHz, ¿cómo te afecta el ruido de los motores eléctricos? Si eliges 5 GHz, ¿cómo solucionarías el problema de los muros?
2. **Priorización de Tráfico (QoS):** ¿Cómo configurarías la red para que los datos del paciente tengan prioridad sobre el Wi-Fi gratuito que usan las visitas en la sala de espera?
3. **Seguridad:** ¿Por qué no es recomendable usar una red Wi-Fi abierta para transmitir el nivel de saturación de oxígeno de un paciente?

### Resumen para Ingeniería

El Wi-Fi es un medio **no guiado**. A diferencia del cable coaxial o la fibra, no controlamos exactamente por dónde viaja la onda, lo que obliga al ingeniero biomédico a ser un experto en la gestión del espectro radioeléctrico para evitar fallos catastróficos.
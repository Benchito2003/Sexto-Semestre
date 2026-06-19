# 15T60SD1F
**5T60SD1F**, no es ni un MOSFET convencional ni un transistor BJT común, es un **IGBT (Insulated Gate Bipolar Transistor)** de 600V y 15A con un diodo de recuperación rápida integrado.

Esto es excelente para tu proyecto. Los **IGBTs** son los "tanques de guerra" de la electrónica de potencia. Se usan precisamente porque aguantan voltajes y corrientes mucho más altos que un MOSFET normal sin calentarse tanto.

### Lo que esto significa para tu diseño:

1. **Manejo de Puerta (Gate):** El EG2136 que tienes es el compañero ideal para estos IGBTs. Los IGBTs se controlan por **voltaje en la puerta**, igual que los MOSFETs, por lo que el ESP32 (vía el driver) se comunica perfectamente con ellos.
    
2. **Protección:** Como son IGBTs de 600V, el motor que estás manejando es, efectivamente, de una potencia considerable. La resina blanca que viste al principio es **vital**. Al ser componentes que trabajan a alta tensión, esa resina evita que salten arcos eléctricos entre las patas cuando el motor arranca o se detiene bruscamente.
    
3. **El "C35" que tapa al Q1:** Confirma lo que sospechábamos. Esos capacitores ahí montados son "Snubbers". Su trabajo es absorber los picos de voltaje (transitorios) que genera el motor cuando sus bobinas se apagan instantáneamente. **No los muevas ni los quites**, son los que evitan que tus IGBTs exploten por sobretensión.
    

### Tu plan de ataque revisado:

Ahora que sabemos que controlas **IGBTs**, la arquitectura es:

- **ESP32-S3:** Genera 6 señales PWM (a 3.3V).
    
- **Divisores de voltaje:** Rebajan esas señales para que el driver las entienda (si es que no son compatibles a 3.3V, aunque el EG2136 suele ser flexible).
    
- **EG2136 (Driver):** Recibe las señales del ESP32 y las amplifica a ~15V con mucha corriente para cargar y descargar la **Puerta (Gate)** de los IGBTs a gran velocidad.
    
- **IGBTs (15T60SD1F):** Funcionan como interruptores electrónicos que conmutan la corriente de los 110V hacia las bobinas del motor.
    

### Recomendación de Seguridad

Como vas a trabajar con **600V (la capacidad de los IGBTs)** y voltajes industriales:

- **Aislamiento:** Cuando conectes tu ESP32, **nunca** conectes la tierra (GND) del ESP32 directamente a la tierra de la placa de potencia sin verificar si el driver tiene aislamiento galvánico. Si no tiene (y lo más seguro es que no tenga), considera usar **optoacopladores** entre el ESP32 y el EG2136. Esto salvará tu computadora si un IGBT explota.
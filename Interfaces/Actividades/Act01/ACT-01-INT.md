---
tags:
  - Actividad
Materia: "[[MOC-Interfaces|Interfaces Hombre-Maquina]]"
---
**Actividad**

ACTIVIDAD 01. COMUNICACIÓN CON UNA INTERFAZ HOMBRE-MAQUINA PREESTABLECIDA

**Detalle**

**Inicia:**

18/feb/2026 - 00:00 hrs

**Termina:**

23/feb/2026 - 23:45 hrs

**Valor:**

0

**Prerrequisitos**

---

**Descripción**

  
La sección "RX-TX SIMPLE" del software adjunto "ComandosRS232", es una interfaz hombre máquina virtual que incluye una pantalla para despliegue de información, y un teclado numérico para que el usuario interactúe con un equipo, esta interfaz recibe y envía información (comandos y datos) a través de un puerto COM RS-232.  
Utilizando una tarjeta Arduino, ESP32 o similar, generar una aplicación con la que se controlará cuando debe estar activo o inactivo el parpadeo de cada uno de tres LEDS, los cuales cuando estén activos sus parpadeos respectivos uno deberá hacerlo a una frecuencia de 1Hz, otro a 2Hz y el tercero a 5Hz. Para activar, desactivar o consultar el estado de activación del parpadeo de cada LED deberá generarse con ayuda de la interfaz virtual “TX-RX SIMPLE” un menú como el siguiente:

**a)**Desplegar un mensaje de inicio y hacer test de encendido/apagado de tres LEDs de los que se estará activando su encendido/apagado durante la ejecución de la aplicación. Desaparecer mensaje de inicio después de unos segundos y pasar al menú principal.  
  
**b)**Menú principal (menú al que se regresará en las opciones “salir” de los demás)  
1.Activar  
2.Desactivar  
3.Ver estados  
  
**c)**Menú activar secuencia (al elegir una opción del 1 al 3 deberá activarse el parpadeo del led que corresponda, o al elegir 4 regresar al menú principal)  
1.S1  
2.S2  
3.S3  
4.Salir  
  
**d)**Menú desactivar secuencia (al elegir una opción del 1 al 3 deberá desactivarse el parpadeo del led que corresponda, o al elegir 4 regresar al menú principal)  
1.S1  
2.S2  
3.S3  
4.Salir  
  
**e)**Menú ver estados LEDS (al elegir opción 3 del menú principal debe apagarse el led que corresponda a la selección)  
1.ON/OFF  
2.ON/OFF  
3.ON/OFF  
4.Salir

Es importante que el código de la aplicación generada para la tarjeta Arduino, ESP32 o para la arquitectura elegida no utilice ningún retardo para que al interactuar el usuario con el menú se perciba que se puede navegar con fluides sobre el mismo.

Elabore un documento con sus resultados y observaciones, cuidando que cumpla con las características establecidas al inicio del curso, y entréguelo en esta plataforma antes de la fecha y hora máximas establecidas, y no olvide insertar en el documento la imagen con la firma de revisión obtenida.
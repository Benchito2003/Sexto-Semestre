---
tags:
  - Actividad
Materia: "[[MOC-Interfaces|Interfaces Hombre-Maquina]]"
---
# ACTIVIDAD 03. JOYSTICK COMO DISPOSITIVO PARA UNA INTERFAZ HOMBRE-MÁQUINA
**Descripción**

Utilizando un dispositivo joystick conectado a dos bits analógicos (ejes XY de movimiento del joystick) y un bit digital (botón del joystick) de una tarjeta Arduino UNO, Nano, Mega u otra plataforma similar, generar una interfaz hombre máquina que permita operar correctamente con las secciones "CAMBIA VALOR" y “RECORTA IMAGEN” del software adjunto "ComandosRS232".

Para la sección "CAMBIA VALOR" la interfaz con el joystick deberá poder incrementar o decrementar el valor en pantalla al mover su palanca hacia arriba o hacia abajo (o si lo prefiere hacia la derecha o hacia la izquierda) respectivamente, a una velocidad de cambio proporcional a la posición de la palanca, dividiendo el rango de movimiento de la palanca en cuatro velocidades distintas: cero, baja, media y alta. La interfaz hombre-máquina generada deberá permitir superar la prueba temporizada.

Para la sección "RECORTA IMAGEN" la interfaz con el joystick deberá poder desplazar el cursor dentro de la zona de imagen de la aplicación, y con ayuda del botón que incluyen los dispositivos joystick y que se activa al presionar la palanca, marcar los puntos que delimiten el área a recortar de la imagen. El cursor deberá poder desplazarse a una velocidad proporcional a la posición de la palanca, en tres velocidades distintas (cero, baja y alta). La interfaz deberá permitir en un máximo de 30 segundos realizar hasta 5 recortes de diferentes regiones de la imagen.

Nota: nuevamente es importante no usar ningún retardo (delay()) en la aplicación desarrollada a menos que sea la única opción.

Elabore un documento con sus resultados y observaciones, cuidando que cumpla con las características establecidas al inicio del curso, y entréguelo en esta plataforma antes de la fecha y hora máximas establecidas, y no olvide insertar en el documento la firma de revisión obtenida al implementar la actividad.
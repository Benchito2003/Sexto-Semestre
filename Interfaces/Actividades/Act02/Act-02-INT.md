---
tags:
  - Actividad
Materia: "[[MOC-Interfaces|Interfaces Hombre-Maquina]]"
---
**Descripción**

Utilizando dos botones de toque de efecto capacitivo conectados a bits digitales de una tarjeta Arduino-UNO, Nano, ESP32 o similar, generar una interfaz hombre máquina que permita interactuar correctamente con la sección "CAMBIA VALOR" del software adjunto "ComandosRS232". La interfaz hombre máquina a desarrollar debe permitir incrementar y decrementar un valor (un botón incrementa el otro decrementa), con cambios lentos inicialmente, y gradualmente con cambios más rápidos en proporción al tiempo en que se mantengan tocando el botón. Considere también que tocar los dos botones al mismo tiempo no debe generar ningún cambio en el valor a ajustar. Es importante que en el código de la aplicación que se desarrolle no se use ningún retardo (delay()) a menos que sea 100% necesario, en su caso justificar su uso.

Para evaluar que la interfaz hombre-máquina generada para la sección "CAMBIA VALOR" funciona adecuadamente, su uso le deberá permitir a todos los integrantes del equipo superar la prueba temporizada que ahí mismo se incluye (en la revisión el profesor le pedirá a alguno de los integrantes del equipo superar la prueba).

Adicionalmente pruebe los botones de toque bajo las siguientes condiciones y determine lo que se pide en cada caso:

1. Al colocar una mica plástica de acrílico sobre el botón, determinar qué tan gruesa pueda llegar a ser permitiendo aún detectar el toque.
2. Al mojarse las manos determinar si esto influye en la detección del toque.
3. Al tocar los botones teniendo guantes de látex o nitrilo en las manos determinar si esto influye en la detección del toque.
4. Pruebe con distintos tipos de materiales (tela, plástico, metales, madera, entre otros) para tocar el botón, determine cuales permiten y cuales no le permiten al botón detectar el toque.

Elabore un documento con sus resultados y observaciones, cuidando que cumpla con las características establecidas al inicio del curso, y entréguelo en esta plataforma antes de la fecha y hora máximas establecidas, y no olvide insertar en el documento la firma de revisión obtenida al implementar la actividad.
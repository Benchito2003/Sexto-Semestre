---
tags:
  - Tarea
Materia: "[[MOC-Procesamiento|Procesamiento de señales Biomédicas]]"
---
# Instrucciones
1. **Trabajo previo:** Complete el tutorial de la aplicación filterDesigner de Matlab disponible en [Introducción a Filter Designer - MATLAB & Simulink Example](https://la.mathworks.com/help/signal/ug/introduction-to-filter-designer.html)  
2. Diseñe un Filtro Pasa-Bajas IIR Butterworth  con frecuencia de muestreo de 1000 Hz, frecuencia de la banda de paso, 100 Hz y frecuencia de la banda rechazada, 150 Hz. Con atenuación en la banda de paso de 1 dB y de 60 dB en la banda rechazada. Responda las siguientes preguntas: ¿Cuál es el orden del filtro resultante? Observe el diagrama de polos y ceros. ¿Qué tan cerca están los polos del círculo unitario?
3. Sin cambiar las frecuencias, cambie el método de diseño a FIR - Equiripple. Compare el orden del filtro. Observe la fase. ¿Cómo es la respuesta en fase de un filtro FIR comparado con uno IIR?
4. Exporte los coeficientes de los filtros diseñados al espacio de trabajo de Matlab. Genere una señal sinusoidal de 80 Hz contaminada con una interferencia de 300 Hz y aplique los filtros a la señal contaminada.
5. Realice una comparación de ambos filtros con los coeficientes resultantes, los diagramas de polos y ceros, su respuesta de amplitud y fase y el efecto de su aplicación a la señal contaminada.

# Archivo(s) de la tarea
![[TutorialFilterDesign_RubenAlfonso.pdf]]
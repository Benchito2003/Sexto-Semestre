---
tags:
  - Actividad
Materia: "[[MOC-Procesamiento|Procesamiento de señales Biomédicas]]"
---
## 1.0 Trabajo previo:
### 1.2 Preparación del entorno
==NOTA: la información importante en la base de datos se encuentra en nombre_del_archivo.hea, y se interpreta: numero_registro numero_canales frecuencia_en_Hz numero_datos==
- Entre a la página del [MIT-BIH Arrhythmia Database] (https://physionet.org/content/mitdb/1.0.0/) y lea la descripción de los registros 100 y 203.
	1. ¿Cuál es la frecuencia de muestreo de estos registros? *Las grabaciones se digitalizaron a **360 muestras por segundo**(360Hz) por canal con una resolución de 11 bits en un rango de 10 mV. Fueron tomadas durante media hora*
	2. ¿Qué derivaciones cardiacas se grabaron en el canal 0 y canal 1 del registro 100? *el canal 0 corresponde a la derivación MLII y el canal 1 corresponde a la derivación V5*
- Entre a la página del CHB-MIT Scalp EEG Database v1.0.0 (https://physionet.org/content/chbmit/1.0.0/) y explore el archivo chb01-summary.txt.
	1. ¿Cuántos canales tiene el registro? *23*
	2. ¿Cuál es la duración del registro? *46 horas*
	3. ¿Cuál es la frecuencia de muestreo? *260 Hz* 
### 1.3 Ejercicio analítico
Dada la secuencia 𝑥 = [0.00,0.52,0.94,0.36,0.97,0.51,1.08,0.42,0.74,0.03, 0.41, −0.12,0.22, −0.38, −0.09, −0.57, −0.34, −0.88, −0.61, −1.02, −0.55, −0.17,0.28,0.67,0.31,0.89,0.46,1.02,0.64,0.18, −0.26, −0.71, −0.33, −0.79, −0.21,0.35,0.74,0.29,0.83,0.40, −0.11, −0.63, −0.27, −0.82, −0.45, 0.02,0.51,0.16,0.68,0.24], calcule: 
1. La media y la varianza. 
2. La autocorrelación para un retraso de 𝑘 = 1. 3. 
3. Interprete los resultados de los puntos anteriores. 
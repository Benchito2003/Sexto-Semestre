---
tags:
  - Tema
Materia: "[[MOC-Procesamiento|Procesamiento de señales Biomédicas]]"
---
# señales
## Visto en clase:
- [[procesamiento-2026-02-11]]
## Contenido
- Señal. Fenómeno que transmite información. Función de una o varias variables que transmite información útil
- Señal unidimensional
- Señal multidimensional
- Señal biológica
- Señal Biomédica

**Señal biomédica**
 - no vienen solas, a veces vienen con "ruido"
	 - $EEG(t) = EEG + ECG + BCG +60Hz$
 - Convertir una serie de tiempo en métricas de diagnóstico
	 - frecuencia respiratoria, variabilidad cardíaca, bandas de potencia de EEG

El proceso de señales biomédicas no es una panacea, se requiere de una buena instrumentación para que sea útil.

Para la transmisión de datos, se tienen que reducir los datos reales y se reconstruyen de manera que sean idénticas a las originales.

*método de medida indirecto*. Es cuando para una medición, aplicamos un valor conocido, aplicamos una formula matemática y obtenemos un resultado. Por ejemplo un oxímetro.

- **Señales Bioelectricas**: Generadas por células nerviosas
- **Señales Bioópticas**: Relacionadas con funciones ópticas del sistema biológico: PPG, SpO2, señales de fluorescencia.
- **Señales de Bioimpedancia**: Obtenida mediante la inyección de corrientes sinusoidales en el tejido: Composición tisular, volumen sanguíneo, actividad nerviosa autónoma. La impedancia en el cuerpo se calcula de manera similar a la impedancia eléctrica: inyectando una corriente y calculando la caída de tensión.
- **Señales Bioacústicas**: Producidas por fenómenos biomédicos que generan ruido acústico
- **Señales Biomagnéticas**: 
- **Señales Biomecánicas**:
- **Señales Bioquímicas**: Resultado de mediciones químicas: concentración de iones, glucosa

**Características de las señales biomédicas** 
	(Todas las señales biológicas son de origen analógico)
- Amplitud: continua o discreta
- Tiempo: Continuo o discreto
- Frecuencia: Ancho de banda (*Es la longitud medida en Hz, del rango  de frecuencias en el que se concentra la mayor parte de la potencia de la señal. Puede ser calculado a partir de una señal temporal*)
- Adquisición: Directa o indirecta

## Notas
- Señal biomédica != Señas biológica
- BCG. Es el movimiento del cuerpo provocados por los latidos del corazón
- Una señal continua en tiempo y amplitud es una señal *Analógica*
## Resumen
Explica el tema en 2–4 líneas como si se lo contaras a alguien



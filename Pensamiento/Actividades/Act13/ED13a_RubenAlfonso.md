# Proyecto de Pensamiento Crítico para la Solución de Problemas (PPCpSP)

**Nombre:** Alfonso Gamboa Rubén  
**Tema:** Reducción de errores en sensores de glucosa no invasivos mediante el uso de Inteligencia Artificial y procesamiento de señales.  
**Área Disciplinar:** Ingeniería Biomédica  
**Fecha:** 31 de mayo de 2026  

---

## 1. Introducción

El presente documento académico tiene como objetivo estructurar una solución viable a un problema disciplinar dentro de la ingeniería biomédica, utilizando el pensamiento crítico. A menudo, en el ámbito escolar y técnico, se confunde la solución de un "problema" con la ejecución de un "ejercicio"[cite: 16]. Un ejercicio se resuelve aplicando rutinas automatizadas, mientras que un problema real es una situación nueva que requiere el uso estratégico de técnicas conocidas[cite: 16]. La elaboración de este proyecto requirió la identificación rigurosa de variables dinámicas, separando las causas raíz de los síntomas superficiales. Se concluye que un documento académico no es solo una recolección de datos, sino un ejercicio argumentativo lógico que justifica la viabilidad técnica de una propuesta frente a la incertidumbre.

## 2. Delimitación de la Situación Problemática (Diagnóstico y Contexto)

El problema abordado surge de una necesidad médica y tecnológica: medir la glucosa en sangre de forma continua y no invasiva[cite: 12]. Este tema es altamente pertinente, ya que los errores en los sensores pueden afectar directamente la salud de los pacientes diabéticos[cite: 12].

* **Contexto:** La problemática impacta la vida de los pacientes, los sistemas hospitalarios y el desarrollo tecnológico general[cite: 12].
* **Pregunta Problemática:** ¿De qué manera se pueden reducir los errores de medición en sensores de glucosa no invasivos causados por el ruido de las bioseñales y las condiciones del paciente?[cite: 18]
* **Variables Generales:** Precisión del sensor, método de medición y condiciones del paciente[cite: 12].
* **Variables Particulares:** Nivel de glucosa detectado, factores dinámicos (como el sudor o la temperatura), y ruido inherente a las pequeñas bioseñales y al hardware del sensor[cite: 12].

## 3. Fundamentos Teórico-Metodológicos (Aparato Crítico)

El análisis de este problema requiere un enfoque interdisciplinar, ya que la medicina por sí sola no puede resolver los fallos del hardware[cite: 12]. Se integran las siguientes áreas:

* **Electrónica:** Para el análisis del funcionamiento de los sensores y circuitos físicos[cite: 12].
* **Informática:** Para el procesamiento de datos y uso de algoritmos avanzados[cite: 12].
* **Medicina:** Para el control y tratamiento efectivo de la diabetes[cite: 12].

La precisión de un sensor no invasivo se ve comprometida por el "ruido" biológico y electrónico [Villena Gonzales et al., 2019](cite: 18). La falta de un software de calibración dinámica produce altos márgenes de error en la detección de los niveles reales de glucosa en sangre[cite: 18].

## 4. Alternativas de Solución (Esquemas Lógicos)

Para abordar las variables identificadas, se plantearon las siguientes alternativas estructuradas lógicamente:

1. **Silogismo hipotético (Enfoque Matemático):** Si aplicamos transformadas matemáticas (Fourier y Laplace) a las señales obtenidas (Rangayyan, 2015), entonces lograremos filtrar el ruido de las pequeñas bioseñales y del sensor[cite: 18]. Si filtramos correctamente el ruido, la precisión de las mediciones de glucosa mejorará[cite: 18].
2. **Argumento Abductivo (Enfoque Algorítmico):** Las condiciones del paciente (como el sudor y la temperatura) introducen variables dinámicas que causan errores de medición[cite: 18]. La inteligencia artificial ha demostrado ser altamente eficaz para reconocer patrones y compensar variables dinámicas en tiempo real [Goodfellow et al., 2016](cite: 18). Por lo tanto, es probable que la integración de inteligencia artificial en el software mejore la calidad de los datos obtenidos[cite: 18].

## 5. Propuesta de Solución Seleccionada y Justificación

**Solución elegida:** Integración de algoritmos de Inteligencia Artificial (IA) junto con transformadas matemáticas (Fourier y Laplace) para mejorar la calidad del software empleado en la lectura del sensor[cite: 12].

**Justificación Argumentativa:**
La solución a los fallos en la medición no invasiva de glucosa no radica únicamente en el cambio físico de los componentes electrónicos, sino en el tratamiento lógico de la información. Las bioseñales son inherentemente ruidosas, y factores externos como la sudoración o la fluctuación de la temperatura corporal alteran la impedancia y las lecturas fotopletismográficas.

Implementar filtros basados en Transformadas de Fourier permite pasar del dominio del tiempo al dominio de la frecuencia, aislando las frecuencias específicas que corresponden a la glucosa y descartando el "ruido" de alta frecuencia generado por la estática o el movimiento del paciente. Sin embargo, el filtrado matemático clásico es estático. Es aquí donde la Inteligencia Artificial justifica su integración: una red neuronal entrenada puede reconocer patrones de error dinámicos. Si la IA detecta que la temperatura de la piel del paciente está subiendo (lo que normalmente alteraría la lectura y daría un falso positivo), el algoritmo compensa matemáticamente esa desviación en tiempo real antes de mostrar el resultado en la pantalla.

Esta solución resuelve el problema de raíz (resolución) al crear un sistema adaptativo. Se logra diseñar un dispositivo más cómodo, eficiente y confiable, mitigando los errores técnicos que afectan directamente la calidad de vida del paciente[cite: 12, 18].

## 6. Conclusiones y Metacognición

El desarrollo de este proyecto integrador me permitió observar mi evolución analítica. Al inicio de mi formación, mi forma natural de resolver problemas técnicos tenía bases empíricas de descarte, pero actuaba movido por el estrés o el ensayo y error[cite: 19].

Ahora entiendo que al estructurar un problema a través de modelos lógicos, puedo aislar de forma consciente las variables (hardware vs. software) sin dejarme llevar por la frustración inicial[cite: 19]. Comprendo que la solución de un problema técnico en la ingeniería biomédica no es un acto de magia ni un golpe de suerte, sino un proceso argumentativo donde uso los datos duros para formular hipótesis lógicas[cite: 19]. Esta estructuración metodológica me vuelve un ingeniero mucho más analítico y eficiente al depurar y diseñar sistemas complejos.

## 7. Referencias Bibliográficas

* Antonio, H. (2017). Organizador DICOP como modelo para el planteamiento de problemas. Universidad Veracruzana.
* Goodfellow, I., Bengio, Y., & Courville, A. (2016). Deep Learning. MIT Press.
* Pozo, J. I. et al. (1994). La solución de problemas. Editorial Santillana / Aula XXI.
* Rangayyan, R. M. (2015). Biomedical Signal Analysis (2nd ed.). IEEE Press / Wiley.
* Villena Gonzales, W., Mobashsher, A. T., & Abbosh, A. (2019). The progress of glucose monitoring—A review of invasive to minimally and non-invasive techniques, devices and sensors. Sensors, 19(4), 800.

# Plantilla COMSOLP - Actividad 12

**Nombre de la institución:** Universidad Veracruzana  
**Región:** Xalapa, Veracruz  
**Carrera:** Ingeniería Biomédica  
**Nombre:** Alfonso Gamboa Rubén  
**Facultad:** Instrumentación Electrónica  

| No. | Actividad | 1ª Respuesta (Pre-test o diagnóstica) | 2ª Respuesta (Post-test / Evaluativa) |
| :--- | :--- | :--- | :--- |
| **1** | Define lo que es “Problema” | Todo aquel obstáculo que impide o ralentiza algún objetivo o fin. | Es una necesidad u obstáculo en un sistema que genera incertidumbre, el cual requiere adquirir un nuevo aprendizaje o aplicar un método analítico estructurado para superarlo de forma definitiva. |
| **2** | Describe algún problema que hayas tenido. | Realicé un código para arduino para leer el contenido de un oxímetro, sin embargo al momento de graficar los datos, se obtenía una gráfica muy errática y llena de “ruido” y no sabía el ¿Por qué?.| Incertidumbre en la transmisión de bioseñales de un oxímetro debido a la presencia de ruido generado por variables no identificadas (hardware, código o software de lectura). |
| **3** | Explica por qué consideras que se trató de un problema. | Porque imposibilitaba la correcta graficación del oxígeno en sangre. | Porque representaba una discrepancia entre el estado ideal del sistema y la ejecución real, exigiendo un proceso de diagnóstico y toma de decisiones para aislar el fallo. |
| **4** | ¿Cuáles son (eran) las características principales de ese problema? | No se sabía el origen del “ruido”, no se sabia si era error del código o del oxímetro, | Había múltiples variables compitiendo entre sí, datos blandos engañosos (se creía que el hardware fallaba) y requería formular hipótesis lógicas para descartar componentes. |
| **5** | ¿Qué tipo de problema consideras que es (fue)? | Un problema con solución lógica y clara | Un problema disciplinar técnico-práctico en un contexto de incertidumbre. |
| **6** | Menciona qué actitud tuviste al estar frente al problema. | Negativa, pues fue estresante la incertidumbre de no conocer la causa. | Al inicio fue una actitud reactiva y pre-reflexiva dominada por la frustración. Ahora tomaría una actitud objetiva, crítica y analítica para no dejar que el estrés nuble el proceso de *debugging*. |
| **7** | Define lo que es “Solución” | Eliminación o mitigación de algún obstáculo que impide o ralentiza algún objetivo o fin. | Es el acto de aplicar el razonamiento intelectual e información fundamentada para elegir la mejor alternativa que remueva un obstáculo de raíz por primera vez, respaldada con argumentos sólidos. |
| **8** | Explica o Argumenta qué hiciste para solucionar el problema. Especifica qué pasos seguiste. | Primero releí mi código, después cambié mi oxímetro con el de otro compañero, finalmente analicé el software con el cual leía el puerto serial, siendo este último el que fallaba por un mal uso, pues graficaba los espacios en blanco como un número “0”. Se desmarcó la casilla “graficar espacios en blanco como 0”. | Apliqué empíricamente un método de diagnóstico similar a DIAPROVE: 1. Diagnóstico de datos blandos (la gráfica tiene ruido). 2. Aislamiento de variables (cambié el sensor físico). 3. Verificación de software (análisis del puerto serial). 4. Solución técnica (ajustar la configuración de lectura de los espacios en blanco). |
| **9** | Explica en qué te basaste para decidir esa solución. | En buscar la raíz del problema, una vez comprendido, la solución es sencilla. | En un proceso lógico de descarte de variables guiado por el pensamiento analítico; me apoyé en datos duros y en el comportamiento esperado del sistema para llegar a la conclusión correcta. |
| **10** | Menciona qué necesitaste para solucionar ese problema (anota todo tipo de necesidad que hayas tenido). | Tuve que pedir prestado materiales de otros compañeros, consultar con profesores y consultar con la inteligencia artifical. | Necesité de un "Aparato Crítico" (documentación, profesores, IA) para tener referentes sólidos, además de herramientas físicas de contraste para aislar el fallo del hardware. |
| **11** | Menciona qué actitud(es) tuviste para solucionar ese problema. | Positiva, pues durante la solución del problema, descubrí que el software que usaba para leer el puerto serial tenía muchas funciones útiles. | Proactiva, indagatoria y abierta al aprendizaje (metacognición). Descubrí que la falla técnica fue una oportunidad para conocer mejor mi entorno de desarrollo. |

---

### Metacognición

**Con mis primeras respuestas “me di cuenta de”:**
Qué el problema en ese momento no era “no grafica”, el problema era “No sé porque no grafica mi código”.

**Con mis segundas respuestas “me di cuenta de”:**
Me di cuenta de que mi forma natural de resolver problemas técnicos ya tenía bases empíricas de descarte, pero actuaba movido por el estrés o el ensayo y error. Ahora entiendo que al estructurar el problema a través de modelos (como ACRISPRO o DIAPROVE), puedo aislar de forma consciente las variables (hardware vs. software) sin dejarme llevar por la frustración inicial. Comprendo que la solución de un problema no es un acto de magia ni un golpe de suerte, sino un proceso argumentativo donde uso los datos duros para formular hipótesis lógicas, lo cual me vuelve un ingeniero mucho más analítico y eficiente al depurar sistemas biomédicos.

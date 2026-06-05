---
Materia: "[[MOC-Sistemas|Sistemas de control]]"
Tipo: Proyecto
---
# Proyecto de sistemas de control
## Equipo
- Alfonso Gamboa Rubén
- Flores Montero Edsel Yetlanezi
## Evaluación

| Criterio  | Valor |
| --------- | ----- |
| Prototipo | 40%   |
| Reporte   | 20%   |

## Propuesta
Aparato que tenga una fuerza fija, aplicando sistemas de control para que esta fuerza sea constante.
## Variable de control
En este caso la variable de control debería ser la **fuerza** misma como un vector donde:
$$F = m\cdot a$$
Esto nos deja con una incógnita interesante, pues la **aceleración** es la **derivada** de la **velocidad** con respecto al **tiempo**:
$$a = \frac{\Delta v}{\Delta t}$$
A su vez, la velocidad se calcula con 
$$v = \frac{d}{t}$$
Entonces nuestras variables lo más simplificadas quedan:
- Distancia
- Tiempo
- Masa

$$F = m \cdot \frac{\Delta \frac{d}{t}}{\Delta t}$$
Por lo que la fórmula de newton no es tan factible.
Como modelar una polea de ejercicio.
Investigar como poder aplicar la ley de hocke para este proyecto.
Investigar el funcionamiento de un motor de grúa.
Un motor que se comporte como se comporte como grua de auto: que especificaciones necesitamos?

## Notas
## Ideas
- Usar un sistema magnético para switchear un sistema mecánico
- Usar un contrapeso, para que el motor eléctrico no consuma mucha corriente (**corriente de arranque o corriente de rotor bloqueado**) pues ahora solo tendría que vencer a la diferencia de peso.
- Poner el motor eléctrico en modo **Generar electricidad**.


## Reporte
---
tags:
  - Tema
Materia: "[[MOC-Sistemas|Sistemas de control]]"
Clases relacionadas:
  - "[[sistemas-2026-02-20]]"
---
# Conducción de calor
El calor es una variable muy lenta de [[¿Qué es control?|controlar]], por lo que el profe gallardo no recomienda trabajar con ella.
La pasta térmica es para eliminar el aire entre el procesador y el disipador, osease **Eliminar el fluido para generar una transmisión de calor por conducción**.
Tenemos 3 formas de transmitir calor.
	- Conducción.
	- Convección.
	- Radiación.
Por lo que tenemos al menos 3 formas de medir calor y cada una tiene su respectiva ecuación.

## conducción: Ley de Fourier
Para el caso simplificado de flujo de calor estacionario en una sola dirección, el calor transmitido es proporcional al área perpendicular al flujo de calor, a la conductividad del material y a la diferencia de temperatura, y es inversamente proporcional al espesor:
$$\frac{Q}{\Delta t} = \frac{kA}{x}(T_1 - T_2)$$

| Símbolo              | Nombre                                                     |
| -------------------- | ---------------------------------------------------------- |
| $\frac{Q}{\Delta t}$ | Calor transmitido por unidad de tiempo                     |
| $k$                  | Conductividad térmica                                      |
| $A$                  | Área de la superficie de contacto                          |
| $x$                  | Espesor del material                                       |
| $(T_1 - T_2)$        | Diferencia de temperatura entre el foco caliente y el frío |


## Convección: Fórmula de la Ley de Convección (Ley de enfriamiento de Newton):
$$\frac{dQ}{dt}=hA_s(T_s-T_{inf})$$

| Símbolo   | Nombre                                    |
| --------- | ----------------------------------------- |
| $h$       | Coeficiente de Convección                 |
| $A_s$     | Área del cuerpo en contacto con el fluido |
| $T_s$     | Temperatura en la superficie del cuerpo   |
| $T_{inf}$ | Temperatura del fluido lejos del cuerpo   |

![[ecuación de la ley de ferviente de newton]]


## Radiación: Ley de plank
"Esta ley es peculiar, pues plank descubrió así la física cuántica y no se dio cuenta" (*profe Gallardo*)

## Notas
- El ventilador genera conveccion forzada al hacer pasar un fluido (el aire) por las ranuras del disipador
## Resumen
Explica el tema en 2–4 líneas como si se lo contaras a alguien
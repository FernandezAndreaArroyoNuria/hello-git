
#Titulo: Proyecto Cloe
**Author:**Andrea Fernández & Nuria Arroyo
**Date:**14/05/2023
**Subject:**ADE, SIEAV

El Proyecto Cloe es un sistema basado en Raspberry Pi que utiliza un sensor ultrasónico para medir 
la distancia a un objeto y controla los movimientos de un robot de cuatro patas (cuadrúpedo) en función de esa distancia.

#Requisitos
- Raspberry Pi con la biblioteca pigpio instalada.
- Conexión de hardware:
	- Sensor ultrasónico conectado a los pines GPIO 6 (TRIG_PIN) y 5 (ECHO_PIN).
	- Dos servomotores conectados a los pines GPIO especificados para cada pierna del robot, en total 4 servomotores.

#Funcionamiento
El programa main.c contiene el código principal para el control del robot. Aquí hay un resumen de las funciones principales:

- setup(): Inicializa los pines GPIO y configura el sensor ultrasónico y los servomotores.
- get_distance(): Utiliza un sensor ultrasónico para medir la distancia a un objeto y devuelve la distancia en centímetros.
- move_servo(): Mueve un servomotor a un ángulo específico.
- turn(): Mueve una de las patas del robot (la izquierda) para girar.
- move(): Mueve las patas del robot hacia adelante.

En el bucle principal main(), el programa mide continuamente la distancia al objeto utilizando el sensor ultrasónico. 
Si la distancia es mayor que 20 cm, el robot avanza moviendo las patas hacia adelante. Si la distancia es menor o igual a 20 cm, 
el robot gira.

#Uso
Clone este repositorio en su Raspberry Pi.
Compile el código usando un compilador cruzado C.
Ejecute el programa compilado main 'proyecto_cloe'.



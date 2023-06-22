# segundop_SPD

**Sistema de incendio -- Arduino**

- Objetivo
- Componentes necesarios
- Conexiones
- Control remoto
- Detección de temperatura
- Sistema de alarma
- Mensajes en el display LCD


Objetivo:

- Diseñar un sistema de incendio utilizando Arduino que pueda detectar cambios de temperatura
- activar un servo motor en caso de detectar un incendio.
- mostrar la temperatura actual y la estación del año en un display LCD.

Componentes necesarios:

Arduino UNO
Sensor de temperatura
Control remoto IR (Infrarrojo)
Display LCD (16x2 caracteres)
Servo motor
Cables y resistencias según sea necesario
Protoboard para realizar las conexiones
Dos leds.

Conexiones:
Conecta el sensor de temperatura al pin analógico A0 de Arduino.
Conecta el control remoto IR al pin digital 11 de Arduino.
Conecta el display LCD utilizando los pines correspondientes de Arduino.
Conecta el servo motor a uno de los pines PWM de Arduino (por ejemplo, pin 9).

Control remoto:
Configura el control remoto IR para recibir señales.
Define los comandos necesarios para activar y desactivar el sistema de incendio.
Utiliza un algoritmo para determinar la estación del año (por ejemplo, rangos de temperatura
para cada estación).
Detección de temperatura:
Configura el sensor de temperatura y realiza la lectura de la temperatura ambiente.
Muestra la temperatura actual en el display LCD.


Sistema de alarma:
Define un umbral de temperatura a partir del cual se considera que hay un [Segundo parcial SPD.pdf]
incendio (por
ejemplo, temperatura superior a 60 grados Celsius).
Cuando se detecta un incendio (temperatura por encima del umbral), se activa el servo
motor para simular una respuesta del sistema de incendio.
Mensajes en el display LCD:
Muestra la temperatura actual y la estación del año en el display LCD.
Cuando se detecta un incendio, muestra un mensaje de alarma en el display LCD.


![image](https://github.com/sebasartorato/segundop_SPD/assets/86857108/99856e7c-1521-4e32-88e1-a7b7542c89e9)

**Diagrama esquemático:**
(https://github.com/sebasartorato/segundop_SPD/files/11840063/Segundo.parcial.SPD.pdf)

**Link del Proyecto:**
https://www.tinkercad.com/things/5x3Cb5nNQJO-segundo-parcial-spd/editel?sharecode=Q6paYDfQQ6B8NtYk9NaXz0cRMMq_PzSscTqGUYolE5c


**Documentación código:**

Utilicé include para importar bibliotecas del LCD, Servo y control infrarrojo.

#include <LiquidCrystal.h> // Para el LCD
#include <IRremote.h> // Para el Control IR
#include <Servo.h>

Definí las constantes para los pines.

#define SENSOR_TEMPERATURA A0
#define LED_1 12
#define LED_2 13 
#define CONTROL_IR 11
#define SERVOMOTOR 9
#define limiteTemperatura 50 



irRecibidor: recibe como parametro el pin del control IR
lcd: recibe los parametros de los pines del LCD
servoMotor: se utiliza para controlar el servomotor


**Función controlRemotoIR** 

Se utiliza para tomar el estado del control remoto y luego prender led izquierdo si es que se baja de temperatura y led derecho si se sube.

**Función estacionAnio**

Función que se utiliza para determinar la estación según la temperatura.

**Función imprimirTemperatura**

Funcion que imprime la temperatura y la estación del año en el LCD.

**Función prendeApagaLed**

Función que apaga y prende leds según sus parámetros.

**Función alarmaIncendio**

Función que imprimi 'Incendio' en el LCD al sobrepasar el límite de temperatura.

**Función titilarLeds**

Función que titila los leds cuando hay un incendio.

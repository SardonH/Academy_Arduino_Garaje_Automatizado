# Academy_Arduino_Garaje_Automatizado

Descripción general del proyecto: 

Este proyecto busca crear un garaje automatizado que reconozca objetos a cierta distancia y automáticamente se active la puerta. 
Para ello se han usado un total de 5 componentes. Sensor Ultrasonidos, Ster Motor + Módulo de traducción para arduino, display LCD, una LED Roja y una LED Verde. 

El código se divide en 4 partes:

1) Librerias, creacion de objetos y variables globales:
Las librerías utillizadas son <Wire.h> (Comunicación I2C para el LCD), <Stepper.h> (Para controlar el ster motor a través del módulo de traducción) y <LiquidCrystal_I2C.h> (Para la pantalla LCD con protocolo I2C).
Por otro lado se instanciaron el Ster Motor, la pantalla LCD y se crearon variables globales para monitorear el estado de la puerta y recordar los pines de cada componente.

2) void setup:
Se indicaron los pines de entrada y salida de componentes como las luces led, los pines de trigger y echo del ultrasonidos.
También se ajustaron parámetros como la velocidad del ster motor, y la activación de la lcd junto con la luz trasera.

3) void loop:
Comprueba si se cumple una de las dos condiciones siguientes.
- distancia recibida del ultrasonidos es menor a 20 cm y si variable bool puertaAbierta == false.
- distancia recibida del ultrasonidos es mayor a 20 cm y si variable bool puertaAbierta == true.

Si la primera condición se cumple: 
- LCD muestra Garaje: ABIERTO
- LED roja (apagada), LED verde (encendida)
- ster motor gira 90 grados.
- bool puertaAbierta = true

Si la segunda condición se cumple:
- LCD muestra Garaje: CERRADO
- LED roja (encendida), LED verde (apagada)
- ster motor gira -90 grados (vuelve a la posición inicial)
- bool puertaAbierta = false

4) función int medirDistancia().
Manda una señal a traves de trigger y luego calcula cuanto tiempo esta activado echo para calcular la distancia entre el objeto y el módulo.

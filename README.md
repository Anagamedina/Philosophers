# Philosophers
Nunca pensé que la filosofía llegara a ser tan letal


## Descripción

Este proyecto resuelve el **Problema de los Filósofos Comensales**, un clásico en programación concurrente. El problema consiste en simular una mesa redonda con filósofos que piensan, comen y duermen, mientras compiten por recursos compartidos (tenedores). El objetivo es evitar condiciones de carrera y asegurarse de que cada filósofo pueda comer sin caer en un estado de "hambre eterna".

### ¿Cómo funciona?
- **Filósofos**: Cada filósofo alterna entre pensar, comer y dormir.
- **Tenedores**: Cada filósofo necesita dos tenedores para comer. Solo puede tomar un tenedor de la mesa si está disponible.
- **Sincronización**: Usamos **hilos** (`pthread`) para simular la concurrencia de los filósofos y evitar condiciones de carrera al compartir los tenedores.

## Características

- **Concurrencia**: Utiliza **hilos (`pthread`)** para simular que varios filósofos realizan acciones al mismo tiempo.
- **Colores**: La salida del programa está coloreada para facilitar la lectura y diferenciar entre las acciones de los filósofos (pensar, comer, dormir y morir).
- **Control de muertes**: Cada filósofo tiene un tiempo limitado para comer, después de lo cual "muere". Esto está controlado por el parámetro de **tiempo de muerte**.
- **Parámetros configurables**:
  - Número de filósofos
  - Tiempo para morir
  - Tiempo para comer
  - Tiempo para dormir
  - (Opcional) Número de veces que cada filósofo debe comer

## Requisitos

- **Compilador**: Se usa `gcc` o `clang` para compilar el programa.
- **Librería**: Se requiere la librería `pthread` para manejar los hilos.

## Instalación

1. Clona este repositorio:

   ```bash
   git clone https://github.com/tu-usuario/philosophers.git
   cd philosophers
### Detalles de las carpetas y archivos:

- **Makefile**: Archivo utilizado para compilar el proyecto y generar el ejecutable.
- **README.md**: Este archivo, que contiene toda la información del proyecto.
- **include/philo.h**: Contiene las definiciones de las estructuras de datos y los prototipos de las funciones. Este archivo se incluye en los archivos fuente para la declaración de funciones y estructuras.
- **src/**: Contiene los archivos fuente en C que implementan la lógica de la simulación.
  - **main.c**: Es el punto de entrada del programa, donde se gestionan los filósofos, su ciclo de vida (pensar, comer, dormir) y la inicialización de los hilos.
  - **parse_args.c**: Contiene funciones para parsear los argumentos de entrada al programa, asegurándose de que se pasen correctamente y se validen.
  - **parse_utils.c**: Funciones auxiliares que gestionan la sincronización de los hilos, controlan el tiempo de vida de los filósofos y se encargan de la interacción con los tenedores.
- **obj/**: Carpeta donde se almacenan los archivos objeto generados al compilar el código (creados por el Makefile). Estos archivos no deben ser editados directamente.



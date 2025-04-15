# Philosophers
Nunca pensé que la filosofía llegara a ser tan letal

# Resumen del Proyecto Philosophers

## 🎯 Objetivo
Simular el problema clásico de los filósofos comensales utilizando hilos (pthread) y mutexes para coordinar la toma de tenedores, evitar condiciones de carrera y detectar la muerte de un filósofo si no come a tiempo.

## 🧵 Hilos utilizados
- **Un hilo por filósofo (`philosopher_routine`)**: come, duerme y piensa, usando mutexes para los tenedores.
- **Un hilo monitor (`monitor_simulation`)**: supervisa si algún filósofo ha muerto o si todos han comido lo requerido.

## ⏱️ Control de tiempo de vida
Cada filósofo tiene un `death_timer` que se actualiza justo después de comer. El monitor revisa si el tiempo actual lo ha sobrepasado para declarar la muerte.

## 🧠 Función clave de muerte
`check_philo_death()` comprueba si el filósofo ha pasado su tiempo límite sin comer y termina la simulación con `safe_end_simulation()` si es necesario.

## 🔚 Fin de la simulación
La simulación termina si un filósofo muere o todos han comido las veces requeridas. Esto se controla mediante el campo `simulation_over`.

## 🔐 Sincronización
- **Tenedores**: mutex por tenedor.
- **Impresiones**: `print_mutex` evita superposición de mensajes.
- **Fin de simulación**: `end_mutex` protege `simulation_over`.
- **Acceso al `death_timer`**: cada filósofo tiene su propio mutex `deadline_to_eat`.

## 📦 Control de casos especiales
- **1 filósofo**: muere tras tomar un solo tenedor.
- **Filósofos impares**: se retrasa su inicio.
- **Todos revisan `simulation_over`** antes de actuar y liberan recursos si es necesario.

## ✅ Resultado final
La implementación detecta correctamente muertes, evita condiciones de carrera, y gestiona correctamente el fin de la simulación, funcionando tanto en modo ilimitado como con número de comidas definido.


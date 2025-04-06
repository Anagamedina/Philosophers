/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:12:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/04 16:48:07 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philosophers(t_config *config)
{
	int i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		config->philos[i].id = i + 1;  // Asignamos el ID al filósofo (1 a N)
		config->philos[i].meals_eaten = 0;  // Inicializamos las comidas a 0
		config->philos[i].last_meal_time = get_time_in_ms();  // Inicializamos el tiempo de la última comida con el tiempo actual
		config->philos[i].config = config;  // Asignamos la configuración global
		config->philos[i].left_fork = &(config->forks[i]);  // Asignamos el tenedor izquierdo

		// Inicializamos el mutex para el tiempo de la comida
		pthread_mutex_init(&config->philos[i].meal_mutex, NULL);

		// Asignamos el tenedor derecho
		if (i == 0)
			config->philos[i].right_fork = &(config->forks[config->number_of_philosophers - 1]);  // El primer filósofo toma el último tenedor
		else
			config->philos[i].right_fork = &(config->forks[i - 1]);  // Los demás filósofos toman el tenedor anterior

		i++;
	}
	config->simulation_time = get_time_in_ms();  // Marcamos el tiempo de inicio de la simulación
}

/*void init_philosophers(t_config *config)
{
    int i;

    i = 0;
    while (i < config->number_of_philosophers)
    {
    	config->philos[i].id = i + 1;  // Asignamos el ID al filósofo (1 a N)
        config->philos[i].meals_eaten = 0;  // Inicializamos las comidas a 0
        config->philos[i].last_meal_time = 0;  // Inicializamos el tiempo de la última comida
        config->philos[i].config = config;  // Asignamos la configuración global
        config->philos[i].left_fork = &(config->forks[i]);
    	pthread_mutex_init(&config->philos[i].meal_mutex, NULL);
        if (i == 0)
        	philos[i].right_fork = &(config->forks[config->number_of_philosophers -1 ]);
		else
		{
        	philos[i].right_fork = &(config->forks[i - 1]);
		}

        i++;
    }
	config->simulation_time = get_time_in_ms();
}
*/
int create_threads(t_config* config)
{
    int i = 0;

    while (i < config->number_of_philosophers)
    {
        if (pthread_create(&(config->threads[i]), NULL, &philosopher_routine, &(config->philos[i])) != 0)
        {
            printf("Error creando el hilo %d\n", i);
            return (1);
        }
        i++;
    }
	return (0);
}


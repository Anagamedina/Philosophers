/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:20:07 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/04 17:21:09 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
void	*monitor_simulation(void *arg)
{
	t_config	*config = (t_config *)arg;
	int			i;

	while (1)
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			pthread_mutex_lock(&config->philos[i].meal_mutex);
			if (get_time_in_ms() - config->philos[i].last_meal_time > config->time_to_die)
			{
				philo_die(config->philos[i].id, config);
				pthread_mutex_unlock(&config->philos[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&config->philos[i].meal_mutex);
			i++;
		}

		if (config->is_limited)
		{
			pthread_mutex_lock(&config->end_mutex);
			if (config->full_philosophers >= config->number_of_philosophers)
			{
				config->simulation_over = 1;
				pthread_mutex_unlock(&config->end_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&config->end_mutex);
		}
		usleep(200); // Dormimos 1ms para no saturar la CPU
	}
	return (NULL);
}
*/

void	*monitor_simulation(void *arg)
{
	t_config	*config;

	config = (t_config *)arg;
	int i;

	while (1)
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			pthread_mutex_lock(&config->philos[i].meal_mutex);
			if ((get_time_in_ms() - config->philos[i].last_meal_time) > config->time_to_die)
			{
				philo_die(config->philos[i].id, config);
				pthread_mutex_unlock(&config->philos[i].meal_mutex);

				pthread_mutex_lock(&config->end_mutex);
				config->simulation_over = 1;
				pthread_mutex_unlock(&config->end_mutex);

				return (NULL); // Salir del monitor si un filósofo muere
			}
			pthread_mutex_unlock(&config->philos[i].meal_mutex);
			i++;
		}

		if (config->is_limited)
		{
			pthread_mutex_lock(&config->end_mutex);
			if (config->full_philosophers >= config->number_of_philosophers)
			{
				config->simulation_over = 1;
				pthread_mutex_unlock(&config->end_mutex);
				return (NULL); // Salir del monitor si todos los filósofos han comido lo suficiente
			}
			pthread_mutex_unlock(&config->end_mutex);
		}
		usleep(200); // Dormimos 200 microsegundos para no saturar la CPU
	}
	return (NULL);
}

int	create_monitor(t_config *config)
{
	pthread_t monitor_thread;

	// Crear el hilo para la función monitor
	if (pthread_create(&monitor_thread, NULL, monitor_simulation, (void *)config) != 0)
	{
		perror("Error creando el hilo del monitor");
		return 1; // Error al crear el hilo
	}

	// Devolver el identificador del hilo si se necesita más tarde
	pthread_detach(monitor_thread); // Desvincula el hilo para que se termine automáticamente
	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:20:07 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/10 10:27:35 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_simulation(void *arg)
{
	t_config	*config;
	int			i;

	config = (t_config *)arg;
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
		usleep(200);
	}
	return (NULL);
}

int	create_monitor(t_config *config)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_simulation, (void *)config) != 0)
	{
		perror("Error creando el hilo del monitor");
		return (1);
	}
	pthread_detach(monitor_thread);
	return (0);
}

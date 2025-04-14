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



int	check_philo_death(t_philos *philo, t_config *config)
{
	int	now;
	int	death_time;

	pthread_mutex_lock(&philo->deadline_to_eat);
	death_time = philo->death_timer;
	pthread_mutex_unlock(&philo->deadline_to_eat);

	now = get_time_in_ms();
	if (now > death_time)
	{
		philo_die(philo->id, config);
		pthread_mutex_lock(&config->end_mutex);
		config->simulation_over = 1;
		pthread_mutex_unlock(&config->end_mutex);
		return (1);
	}
	return (0);
}

int	check_full_philos(t_config *config)
{
	int result;

	pthread_mutex_lock(&config->end_mutex);
	result = (config->full_philosophers >= config->number_of_philosophers);
	if (result)
		config->simulation_over = 1;
	pthread_mutex_unlock(&config->end_mutex);
	return (result);
}

void	*monitor_simulation(void *arg)
{
	t_config	*config = (t_config *)arg;
	int			i;

	while (1)
	{
		if (is_simulation_over(config))
			return (NULL);

		i = 0;
		while (i < config->number_of_philosophers)
		{
			if (check_philo_death(&config->philos[i], config))
				return (NULL);
			i++;
		}

		if (config->is_limited && check_full_philos(config))
			return (NULL);

		usleep(50);
	}
	return (NULL);
}

int	create_monitor(t_config *config)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor_simulation, (void *)config) != 0)
	{
		perror("Error creando el hilo del monitor");
		return (1);
	}
	pthread_detach(monitor_thread);
	return (0);
}

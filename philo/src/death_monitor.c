/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:20:07 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/25 00:40:47 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_end_simulation(t_config *config, int id)
{
	pthread_mutex_lock(&config->end_mutex);
	if (config->simulation_over == 0)
	{
		config->simulation_over = 1;
		pthread_mutex_unlock(&config->end_mutex);
		philo_die(id, config);
	}
	else
		pthread_mutex_unlock(&config->end_mutex);
}

int	check_philo_death(t_philos *philo, t_config *config)
{
	unsigned long	now;

	pthread_mutex_lock(&philo->deadline_to_eat);
	now = get_time_in_ms();
	if (now > philo->death_timer)
	{
		pthread_mutex_unlock(&philo->deadline_to_eat);
		safe_end_simulation(config, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->deadline_to_eat);
	return (0);
}

/*int	check_full_philos(t_config *config)
{
	int	result;

	pthread_mutex_lock(&config->end_mutex);
	if (config->full_philosophers >= config->num_of_philo)
		config->simulation_over = 1;
	result = config->simulation_over;
	pthread_mutex_unlock(&config->end_mutex);
	return (result);
}*/

int	check_full_philos(t_config *config)
{
	int	full = 0;
	int	i = 0;

	while (i < config->num_of_philo)
	{
		pthread_mutex_lock(&config->philos[i].deadline_to_eat);
		if (config->philos[i].is_full == 1)
			full++;
		pthread_mutex_unlock(&config->philos[i].deadline_to_eat);
		i++;
	}
	if (full >= config->num_of_philo)
	{
		pthread_mutex_lock(&config->end_mutex);
		config->simulation_over = 1;
		pthread_mutex_unlock(&config->end_mutex);
		printf("FULL PHILOSOPHERS, THE SIMULATION IS OVER.\n"); // 🎯 Aquí
		return (1);
	}
	return (0);
}


void	*monitor_simulation(void *arg)
{
	t_config	*config;
	int			i;

	config = (t_config *)arg;
	while (!is_simulation_over(config))
	{
		i = 0;
		while (i < config->num_of_philo)
		{
			if (check_philo_death(&config->philos[i], config))
				return (NULL);
			i++;
		}
		if (config->is_limited && check_full_philos(config))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	create_monitor(t_config *config)
{
	if (pthread_create(&config->monitor_thread, NULL, &monitor_simulation, \
				(void *)config) != 0)
	{
		perror("Error creando el hilo del monitor");
		return (1);
	}
	return (0);
}

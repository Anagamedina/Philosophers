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

/*int	check_philo_death(t_philos *philo, t_config *config)
{
	int	now;
	int	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);

	now = get_time_in_ms();
	if (now - last_meal >= config->time_to_die)
	{
		pthread_mutex_lock(&config->end_mutex);
		if (config->simulation_over == 0) // evita mensaje duplicado
		{
			config->simulation_over = 1;
			pthread_mutex_unlock(&config->end_mutex);
			philo_die(philo->id, config); // ¡fuera del mutex!
		}
		else
			pthread_mutex_unlock(&config->end_mutex);
		return (1);
	}
	return (0);
}*/

int	check_philo_death(t_philos *philo, t_config *config)
{
	int	now = get_time_in_ms();

	pthread_mutex_lock(&philo->deadline_to_eat);
	if (now >= philo->death_timer)
	{
		pthread_mutex_unlock(&philo->deadline_to_eat);

		pthread_mutex_lock(&config->end_mutex);
		if (config->simulation_over == 0)
		{
			config->simulation_over = 1;
			pthread_mutex_unlock(&config->end_mutex);
			philo_die(philo->id, config);
		}
		else
			pthread_mutex_unlock(&config->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->deadline_to_eat);
	return (0);
}

int	check_full_philos(t_config *config)
{
	int result;
	pthread_mutex_lock(&config->end_mutex);
	if (config->full_philosophers >= config->number_of_philosophers)
		config->simulation_over = 1;
	result = config->simulation_over;
	pthread_mutex_unlock(&config->end_mutex);
	return (result);

}


void	*monitor_simulation(void *arg)
{
	t_config	*config = (t_config *)arg;
	int			i;

	while (!is_simulation_over(config))
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			if (check_philo_death(&config->philos[i], config))
				return (NULL);
			i++;
		}
		if (config->is_limited && check_full_philos(config))
			return (NULL);
		// usleep(100);
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
/*void	*monitor_simulation(void *arg)
{
	t_config	*config = (t_config *)arg;
	int			i;


	while (1)
	{
		if (!is_simulation_over(config))
			return (NULL);
		i = 0;
		while (i < config->number_of_philosophers)
		{
			if (check_philo_death(&config->philos[i], config))
				return (NULL);
			i++;
		}

		if (config->is_limited == 1 && check_full_philos(config) == 1)
			return (NULL);

		usleep(50);
	}
	return (NULL);
}
*/


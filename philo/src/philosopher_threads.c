/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:12:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/16 20:42:14 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	handle_one_philosopher(t_philos *philo)
{
	t_config	*config;

	config = philo->config;
	if (config->num_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action_color(philo, "has taken a fork", GREEN);
		ft_usleep(config->time_to_die);
		pthread_mutex_unlock(philo->left_fork); //deadlock!!
		safe_end_simulation(config, philo->id);
		return (1);
	}
	return (0);
}

static void	philo_sync_start(t_philos *philo)
{
	t_config	*config;

	config = philo->config;
	while (get_time_in_ms() < config->simulation_time)
		usleep(100);
	pthread_mutex_lock(&philo->deadline_to_eat);
	philo->death_timer = get_time_in_ms() + config->time_to_die;
	pthread_mutex_unlock(&philo->deadline_to_eat);
}

void	philo_delay_if_odd(t_philos *philo)
{
	if (philo->id % 2 == 1)
		ft_usleep(philo->time_to_eat / 2);
}

void	*philosopher_routine(void *arg)
{
	t_philos	*philo;
	t_config	*config;

	philo = (t_philos *)arg;
	config = philo->config;
	philo_sync_start(philo);
	if (handle_one_philosopher(philo) == 1)
		return (NULL);
	philo_delay_if_odd(philo);
	while (is_simulation_over(config) == 0)
	{
		if (philo_take_forks(philo) == 1)
			break ;
		philo_eat(philo);
		if (check_full_and_stop(philo))
		{
			release_forks(philo);
			break ;
		}
		release_forks(philo);
		if (is_simulation_over(config))
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}

int	create_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_of_philo)
	{
		if (pthread_create(&(config->threads[i]), NULL, \
			&philosopher_routine, &(config->philos[i])) != 0)
		{
			printf("Error creando el hilo %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

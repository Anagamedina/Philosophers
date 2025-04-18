/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:26:02 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/17 13:05:00 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philosophers(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_of_philo)
	{
		config->philos[i].id = i + 1;
		config->philos[i].is_full = 0;
		config->philos[i].num_of_philo = config->num_of_philo;
		config->philos[i].time_to_die = config->time_to_die;
		config->philos[i].time_to_eat = config->time_to_eat;
		config->philos[i].time_to_sleep = config->time_to_sleep;
		config->philos[i].max_meals = config->max_meals;
		config->philos[i].meals_eaten = 0;
		config->philos[i].config = config;
		config->philos[i].left_fork = &(config->forks[i]);
		//config->philos[i].death_timer = 0;
		if (i == 0)
			config->philos[i].right_fork \
				= &(config->forks[config->num_of_philo - 1]);
		else
			config->philos[i].right_fork = &(config->forks[i - 1]);
		pthread_mutex_lock(&config->philos[i].deadline_to_eat);
		config->philos[i].death_timer = get_time_in_ms() + config->time_to_die;
		pthread_mutex_unlock(&config->philos[i].deadline_to_eat);
		pthread_mutex_init(&config->philos[i].deadline_to_eat, NULL);
		i ++;
	}
}

void	init_mutex(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_of_philo)
	{
		pthread_mutex_init(&(config->forks[i]), NULL);
		i++;
	}
}

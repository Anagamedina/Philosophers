/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:26:02 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/02 19:09:18 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void init_philosophers(t_config *config)
{
	int i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		config->philos[i].id = i + 1;
		config->philos[i].is_full = 0;
		config->philos[i].number_of_philosophers = config->number_of_philosophers;
		config->philos[i].time_to_die = config->time_to_die;
		config->philos[i].time_to_eat = config->time_to_eat;
		config->philos[i].time_to_sleep = config->time_to_sleep;
		config->philos[i].number_of_times_each_philosopher_must_eat = config->number_of_times_each_philosopher_must_eat;
		config->philos[i].meals_eaten = 0;
		config->philos[i].config = config;
		config->philos[i].left_fork = &(config->forks[i]);
		config->philos[i].death_timer = 0;
		//config->philos[i].death_timer = config->simulation_time + config->time_to_die;
		if (i == 0)
			config->philos[i].right_fork = &(config->forks[config->number_of_philosophers - 1]);
		else
			config->philos[i].right_fork = &(config->forks[i - 1]);
		pthread_mutex_init(&config->philos[i].deadline_to_eat, NULL); // dead_timer
		i ++;
	}
}

void	init_mutex(t_config *config)
{
	int i = 0;

	while (i < config->number_of_philosophers)
	{
		pthread_mutex_init(&(config->forks[i]), NULL);
		i++;
	}
}


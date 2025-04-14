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

	int now = get_time_in_ms();
	config->simulation_time = get_time_in_ms();  // Marcamos el tiempo de inicio de la simulación
	i = 0;
	while (i < config->number_of_philosophers)
	{
		config->philos[i].id = i + 1;
		config->philos[i].meals_eaten = 0;
		//config->philos[i].last_meal_time = get_time_in_ms();
		//config->philos[i].last_meal_time = 0;
		config->philos[i].config = config;
		config->philos[i].left_fork = &(config->forks[i]);
		config->philos[i].last_meal_time = now;
		config->philos[i].death_timer = now + config->time_to_die;
		//config->philos[i].death_timer = config->simulation_time + config->time_to_die;
		if (i == 0)
			config->philos[i].right_fork = &(config->forks[config->number_of_philosophers - 1]);
		else
			config->philos[i].right_fork = &(config->forks[i - 1]);
		i ++;
	}
}

void init_mutex(t_config *config)
{
	int i = 0;

	config->forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_init(&(config->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(config->print_mutex), NULL);
	pthread_mutex_init(&(config->end_mutex), NULL);
	pthread_mutex_init(&config->philos[i].meal_mutex, NULL);
	pthread_mutex_init(&config->philos[i].deadline_to_eat, NULL);
}


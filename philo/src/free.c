/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:53:34 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/15 16:53:37 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philosophers(t_config *config)
{
	int	i;

	if (!config->philos)
		return ;
	i = 0;
	while (i < config->num_of_philo)
	{
		pthread_mutex_destroy(&config->philos[i].deadline_to_eat);
		i++;
	}
	free(config->philos);
	config->philos = NULL;
}

void	free_forks(t_config *config)
{
	int	i;

	if (!config->forks)
		return ;
	i = 0;
	while (i < config->num_of_philo)
	{
		pthread_mutex_destroy(&config->forks[i]);
		i++;
	}
	free(config->forks);
	config->forks = NULL;
}

void	destroy_global_mutexes(t_config *config)
{
	pthread_mutex_destroy(&config->print_mutex);
	pthread_mutex_destroy(&config->end_mutex);
}

void	free_all(t_config *config)
{
	if (config->philos)
		free(config->philos);
	if (config->forks)
		free(config->forks);
	if (config->threads)
		free(config->threads);
}

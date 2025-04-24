/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:52:31 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/25 01:19:53 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_simulation_over(t_config *config)
{
	int	result;

	pthread_mutex_lock(&(config->end_mutex));
	result = config->simulation_over;
	pthread_mutex_unlock(&(config->end_mutex));
	return (result);
}

int	join_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_of_philo)
	{
		if (pthread_join(config->threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_config	config;

	if (is_valid_arguments(ac, av) == 1)
		return (printf("Invalid arguments.\n"), 1);
	if (init_config(ac, av, &config) == 0)
	{
		init_mutex(&config);
		init_philosophers(&config);
		if (config.num_of_philo == 1)
			handle_one_philosopher(&config.philos[0]);
		else
		{
			create_threads(&config);
			if (create_monitor(&config) != 0)
				return (1);
			if (join_threads(&config) == 1)
				return (1);
			pthread_join(config.monitor_thread, NULL);
		}
	}
	else
		return (printf("Invalid arguments.\n"), 1);
	free_forks(&config);
	free_philosophers(&config);
	destroy_global_mutexes(&config);
	free_all(&config);
	return (0);
}

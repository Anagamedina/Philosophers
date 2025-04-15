/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:52:31 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/10 15:34:55 by anamedin         ###   ########.fr       */
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

	config.simulation_over = 0;
	if (init_config(ac, av, &config) == 0)
	{
		init_mutex(&config);
		init_philosophers(&config);
		create_threads(&config);
		if (create_monitor(&config) != 0)
			return (1);
		if (join_threads(&config) == 1)
			return (1);
	}
	else
		printf("Initialization failed.\n");
	if (config.is_limited && config.full_philosophers == config.num_of_philo)
		printf("FULL PHILOSOPHERS, THE SIMULATION IS OVER.\n");
	free_all(&config);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:12:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/04 16:48:07 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	handle_one_philosopher(t_philos *philo)
{
	t_config *config = philo->config;

	if (config->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action_color(philo, "has taken a fork", GREEN);
		ft_usleep(config->time_to_die);
		philo_die(philo->id, config);
		return (1);
	}
	return (0);
}



int	check_full_and_stop(t_philos *philo)
{
	t_config *config = philo->config;

	if (config->is_limited == 1 && philo->meals_eaten >= config->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&config->end_mutex);
		if (!philo->is_full)
		{
			philo->is_full = 1;
			config->full_philosophers++;
			if (config->full_philosophers >= config->number_of_philosophers)
				config->simulation_over = 1;
		}
		pthread_mutex_unlock(&config->end_mutex);
		return (1);
	}
	return (0);
}


void	*philosopher_routine(void *arg)
{
	t_philos	*philo = (t_philos *)arg;
	t_config	*config = philo->config;

	while (get_time_in_ms() < config->simulation_time)
		usleep(100);

	pthread_mutex_lock(&philo->deadline_to_eat);
	philo->death_timer = get_time_in_ms() + config->time_to_die;
	pthread_mutex_unlock(&philo->deadline_to_eat);

	if (handle_one_philosopher(philo) == 1)
		return (NULL);
	if (philo->id % 2 == 1)
		ft_usleep(philo->time_to_eat / 2);
	while (!is_simulation_over(config))
	{
		pthread_mutex_lock(philo->left_fork);
		if (is_simulation_over(config))
		{
			pthread_mutex_unlock(philo->left_fork);
			break;
		}
		print_action_color(philo, "has taken a fork", GREEN);

		pthread_mutex_lock(philo->right_fork);
		if (is_simulation_over(config))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break;
		}
		print_action_color(philo, "has taken a fork", GREEN);

		print_action_color(philo, "is eating", BLUE);
		pthread_mutex_lock(&philo->deadline_to_eat);
		philo->death_timer = get_time_in_ms() + philo->time_to_die;
		pthread_mutex_unlock(&philo->deadline_to_eat);
		ft_usleep(config->time_to_eat);
		philo->meals_eaten++;
		if (check_full_and_stop(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break;
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		if (is_simulation_over(config))
			break;
		print_action_color(philo, "is sleeping", YELLOW);
		ft_usleep(philo->time_to_sleep);

		if (is_simulation_over(config))
			break;
		print_action_color(philo, "is thinking", CYAN);
	}

	return (NULL);
}

int create_threads(t_config* config)
{
    int i = 0;

    while (i < config->number_of_philosophers)
    {
        if (pthread_create(&(config->threads[i]), NULL, &philosopher_routine, &(config->philos[i])) != 0)
        {
            printf("Error creando el hilo %d\n", i);
            return (1);
        }
        i++;
    }
	return (0);
}
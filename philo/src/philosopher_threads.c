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
		print_fork_taken(philo, PRINT_LEFT);
		ft_usleep(config->time_to_die);
		philo_die(philo->id, config);
		return (1);
	}
	return (0);
}

void	take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_fork_taken(philo, PRINT_LEFT);
		pthread_mutex_lock(philo->right_fork);
		print_fork_taken(philo, PRINT_RIGHT);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_fork_taken(philo, PRINT_LEFT);
		pthread_mutex_lock(philo->left_fork);
		print_fork_taken(philo, PRINT_RIGHT);
	}
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


void	release_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


void	*philosopher_routine(void *arg)
{
	t_philos	*philo = (t_philos *)arg;
	t_config	*config = philo->config;
	int			end_flag = 0;

	while (get_time_in_ms() < config->simulation_time)
		usleep(100);

	pthread_mutex_lock(&philo->deadline_to_eat);
	philo->death_timer = get_time_in_ms() + config->time_to_die;
	pthread_mutex_unlock(&philo->deadline_to_eat);

	if (handle_one_philosopher(philo) == 1)
		return (NULL);

	if (philo->id % 2 == 1)
		ft_usleep(philo->time_to_eat / 2);

	while (end_flag == 0)
	{
		// 🔐 Comprobar antes de actuar si la simulación terminó
		pthread_mutex_lock(&config->end_mutex);
		end_flag = config->simulation_over;
		pthread_mutex_unlock(&config->end_mutex);
		if (end_flag)
			break;

		// Tomar tenedores
		pthread_mutex_lock(philo->left_fork);
		print_fork_taken(philo, PRINT_LEFT);
		pthread_mutex_lock(philo->right_fork);
		print_fork_taken(philo, PRINT_RIGHT);

		// Comer
		pthread_mutex_lock(&config->print_mutex);
		printf(GREEN "%d %d is eating\n" RESET,
			get_time_in_ms() - config->simulation_time, philo->id);
		pthread_mutex_unlock(&config->print_mutex);

		pthread_mutex_lock(&philo->deadline_to_eat);
		philo->death_timer = get_time_in_ms() + philo->time_to_die;
		pthread_mutex_unlock(&philo->deadline_to_eat);

		ft_usleep(config->time_to_eat);

		philo->meals_eaten++;

		if (check_full_and_stop(philo) == 1)
			break;

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		// Dormir
		pthread_mutex_lock(&config->end_mutex);
		end_flag = config->simulation_over;
		pthread_mutex_unlock(&config->end_mutex);
		if (end_flag)
			break;

		philo_sleeps(philo->id, config);
		ft_usleep(philo->time_to_sleep);

		// Pensar
		pthread_mutex_lock(&config->end_mutex);
		end_flag = config->simulation_over;
		pthread_mutex_unlock(&config->end_mutex);
		if (end_flag)
			break;

		philo_thinks(philo->id, config);
	}

	// Seguridad: soltar forks si aún los tiene
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

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
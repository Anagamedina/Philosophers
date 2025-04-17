/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:42:04 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/17 13:12:00 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_take_forks(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_simulation_over(philo->config))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_action_color(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(philo->right_fork);
	if (is_simulation_over(philo->config))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_action_color(philo, "has taken a fork", GREEN);
	return (0);
}

void	philo_eat(t_philos *philo)
{
	print_action_color(philo, "is eating", BLUE);
	pthread_mutex_lock(&philo->deadline_to_eat);
	philo->death_timer = get_time_in_ms() + philo->time_to_die;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->deadline_to_eat);
	ft_usleep(philo->config->time_to_eat);
}

void	philo_sleep_and_think(t_philos *philo)
{
	print_action_color(philo, "is sleeping", YELLOW);
	ft_usleep(philo->time_to_sleep);
	if (is_simulation_over(philo->config) == 0)
		print_action_color(philo, "is thinking", CYAN);
}
void	release_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

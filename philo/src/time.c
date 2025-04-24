/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:10:31 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/25 01:12:16 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	get_time_in_ms(void)
{
	struct timeval	tv;
	unsigned long	time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL);
	return (time_ms);
}

void	ft_usleep(unsigned long time_ms)
{
	unsigned long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time_ms)
		usleep(200);
}

void	philo_die(int id, t_config *config)
{
	pthread_mutex_lock(&config->print_mutex);
	printf(RED "%lu %d died\n" RESET, get_time_in_ms() - \
			config->simulation_time, id);
	pthread_mutex_unlock(&config->print_mutex);
}

void	print_action_color(t_philos *philo, const char *action, \
		const char *color)
{
	t_config		*config;
	unsigned long	timestamp;

	config = philo->config;
	if (is_simulation_over(config))
		return ;
	pthread_mutex_lock(&config->print_mutex);
	if (!is_simulation_over(config))
	{
		timestamp = get_time_in_ms() - config->simulation_time;
		printf("%s%lu %d %s%s\n", color, timestamp, philo->id, action, RESET);
	}
	pthread_mutex_unlock(&config->print_mutex);
}

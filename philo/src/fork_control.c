/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:42:04 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/10 11:05:17 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long get_time_in_ms(void)
{
	struct timeval tv;
	unsigned long time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000UL) + (tv.tv_usec / 1000);
	return (time_ms);
}

void ft_usleep(unsigned long time_ms)
{
	unsigned long start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time_ms)
		usleep(100);
}

/****************************************/
void philo_thinks(int id, t_config *config)
{
    pthread_mutex_lock(&config->print_mutex);
    printf(CYAN "%lu %d is thinking\n" CYAN, get_time_in_ms() - config->simulation_time
, id);
    pthread_mutex_unlock(&config->print_mutex);
}

void	philo_sleeps(int id, t_config *config)
{
    pthread_mutex_lock(&config->print_mutex);
    printf(YELLOW "%lu %d is sleeping\n" RESET, get_time_in_ms() - config->simulation_time
, id);
    pthread_mutex_unlock(&config->print_mutex);
}



void	philo_die(int id, t_config *config)
{
	pthread_mutex_lock(&config->print_mutex);
	printf(RED "%lu %d died\n" RESET, get_time_in_ms() - config->simulation_time, id);
	pthread_mutex_unlock(&config->print_mutex);

}


   

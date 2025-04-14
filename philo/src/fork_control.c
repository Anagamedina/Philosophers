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

int get_time_in_ms(void)
{
    struct  timeval tv;
    int     time_ms;

    gettimeofday(&tv, NULL);
    time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time_ms);
}

void ft_usleep(int time_ms)
{
	int  start_time;

    start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_ms)
		// usleep(100);
		usleep(50);
}

/****************************************/
void philo_thinks(int id, t_config *config)
{
    pthread_mutex_lock(&config->print_mutex);
    printf(CYAN "%d %d is thinking\n" CYAN, get_time_in_ms() - config->simulation_time
, id);
    pthread_mutex_unlock(&config->print_mutex);
}

/*void philo_eats(t_philos *philo)
{
	t_config *config = philo->config;

	if (is_simulation_over(config))
		return ;

	pthread_mutex_lock(&config->print_mutex);
	printf(GREEN "%d %d is eating\n" RESET,
		get_time_in_ms() - config->simulation_time, philo->id);
	pthread_mutex_unlock(&config->print_mutex);

	pthread_mutex_lock(&philo->deadline_to_eat);
	philo->death_timer = get_time_in_ms() + config->time_to_die;
	pthread_mutex_unlock(&philo->deadline_to_eat);

	ft_usleep(config->time_to_eat);
}*/
void	philo_sleeps(int id, t_config *config)
{
    pthread_mutex_lock(&config->print_mutex);
    printf(YELLOW "%d %d is sleeping\n" RESET, get_time_in_ms() - config->simulation_time
, id);
    pthread_mutex_unlock(&config->print_mutex);
}



void	philo_die(int id, t_config *config)
{
	pthread_mutex_lock(&config->print_mutex);
	printf(RED "%d %d died\n" RESET, get_time_in_ms() - config->simulation_time, id);
	pthread_mutex_unlock(&config->print_mutex);

}
/********************************************/


   

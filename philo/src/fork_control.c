/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:42:04 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/04 17:35:51 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void ft_usleep(int time_in_ms)
{
	long long start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_in_ms)
		usleep(100);
}


/****************************************/
void philo_thinks(int id, t_config *config)
{
    pthread_mutex_lock(&config->print_mutex);
    printf(BLUE "%d %d is thinking\n" RESET, get_time_in_ms() - config->simulation_time
, id);
    pthread_mutex_unlock(&config->print_mutex);
}

void philo_eats(t_philos *philo)
{
	t_config *config = philo->config;

	pthread_mutex_lock(&config->print_mutex);
	printf(GREEN "%d %d is eating\n" RESET, get_time_in_ms() - config->simulation_time
, philo->id);
	pthread_mutex_unlock(&config->print_mutex);

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);

	ft_usleep(config->time_to_eat);
}

void	philo_sleeps(int id, t_config *config)
{
    pthread_mutex_lock(&config->print_mutex);
    printf(YELLOW "%d %d is sleeping\n" RESET, get_time_in_ms() - config->simulation_time
, id);
    pthread_mutex_unlock(&config->print_mutex);
}

/*void philo_die(int id, t_config *config)
{
    pthread_mutex_lock(&config->print_mutex);
    printf(RED "%d %d died\n" RESET, get_time_in_ms(), id);
    pthread_mutex_unlock(&config->print_mutex);
}*/

void philo_die(int id, t_config *config)
{
	pthread_mutex_lock(&config->print_mutex);  // Bloqueamos el mutex de impresión para evitar condiciones de carrera al imprimir
	printf(RED "%d %d died\n" RESET, get_time_in_ms() - config->simulation_time, id);  // Imprimimos que el filósofo ha muerto
	pthread_mutex_unlock(&config->print_mutex);  // Desbloqueamos el mutex de impresión

	// pthread_mutex_lock(&config->end_mutex);  // Bloqueamos el mutex de finalización para garantizar que la simulación termine
	// config->simulation_over = 1;  // Marcamos la simulación como finalizada
	// pthread_mutex_unlock(&config->end_mutex);  // Desbloqueamos el mutex de finalización
}
/********************************************/


void init_mutex(t_config *config)
{
    int i = 0;

    // Inicializamos el array de mutexes para los tenedores
    config->forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
    while (i < config->number_of_philosophers)
    {
        pthread_mutex_init(&(config->forks[i]), NULL);  // Inicializamos cada mutex de tenedor
        i++;
    }

    // Inicializamos los mutexes de impresión y finalización
    pthread_mutex_init(&(config->print_mutex), NULL);
    pthread_mutex_init(&(config->end_mutex), NULL);
}


   

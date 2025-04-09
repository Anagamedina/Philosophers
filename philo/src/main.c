/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:52:31 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/04 17:36:40 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void print_fork_taken(t_philos *philo)
{
  t_config *config = philo->config;

	pthread_mutex_lock(&philo->config->print_mutex);
	printf(BLUE "%d %d has taken a fork\n" RESET, get_time_in_ms() - config->simulation_time
, philo->id);
	pthread_mutex_unlock(&philo->config->print_mutex);
}

int	is_simulation_over(t_config *config)
{
	int	result;

	pthread_mutex_lock(&config->end_mutex);
	result = config->simulation_over;
	pthread_mutex_unlock(&config->end_mutex);
	return (result);
}


void *philosopher_routine(void *arg)
{
	t_philos *philo = (t_philos *)arg;
	t_config *config = philo->config;

	while (1)
	{
		// pthread_mutex_lock(&philo->config->end_mutex);
		// if (philo->config->simulation_over)
		// {
		// 	pthread_mutex_unlock(&philo->config->end_mutex);
		// 	break;  // Terminar el hilo si la simulación ha terminado
		// }
		// pthread_mutex_unlock(&philo->config->end_mutex);
		philo_thinks(philo->id, config);

		if (philo->id % 2 == 0) {
			pthread_mutex_lock(philo->left_fork);
			print_fork_taken(philo);
			pthread_mutex_lock(philo->right_fork);
			print_fork_taken(philo);
		} else {
			pthread_mutex_lock(philo->right_fork);
			print_fork_taken(philo);
			pthread_mutex_lock(philo->left_fork);
			print_fork_taken(philo);
		}

		philo_eats(philo);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		philo_sleeps(philo->id, config);
		ft_usleep(config->time_to_sleep);

		if (config->is_limited && philo->meals_eaten >= config->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&config->end_mutex);
			config->full_philosophers++;
			// si aquí ya están todos llenos, marcamos el fin
			if (config->full_philosophers >= config->number_of_philosophers)
				config->simulation_over = 1;
			pthread_mutex_unlock(&config->end_mutex);
			break;
		}
		if (config->is_limited && philo->meals_eaten >= config->number_of_times_each_philosopher_must_eat)
			break;
	}
	return NULL;
}

int main(int ac, char **av)
{
	t_config config;
	int i;
	config.simulation_over = 0;

	// Inicialización de la configuración
	if (init_config(ac, av, &config) == 0)
	{
		// Imprimir configuración de comidas limitadas o no
		if (config.is_limited == 1)
			printf("Number of Times Each Philosopher Must Eat: %d\n", config.number_of_times_each_philosopher_must_eat);
		else
			printf("Unlimited eating.\n");
		// Inicializar mutexes y filósofos
		init_mutex(&config);
		init_philosophers(&config);
		// Crear el monitor para supervisar la simulación
		if (create_monitor(&config) != 0)
		{
			printf("Error al crear el monitor\n");
			return (1); // Salir si no se pudo crear el monitor
		}
		// Crear los hilos de los filósofos
		create_threads(&config);
		// Esperar que los hilos de los filósofos terminen
		i = 0;
		while (i < config.number_of_philosophers)
		{
			pthread_join(config.threads[i], NULL);
			i++;
		}
		free(config.philos);
		free(config.forks);
	}
	else
	{
		printf("Initialization failed.\n");
	}

	return 0;
}



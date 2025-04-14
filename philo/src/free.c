#include "../include/philo.h"

void	free_philosophers(t_config *config)
{
	int	i;

	if (!config->philos)
		return;
	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_destroy(&config->philos[i].meal_mutex);
		pthread_mutex_destroy(&config->philos[i].deadline_to_eat);
		i++;
	}
	free(config->philos);
	config->philos = NULL;
}

void	free_forks(t_config *config)
{
	int	i;

	if (!config->forks)
		return;
	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_destroy(&config->forks[i]);
		i++;
	}
	free(config->forks);
	config->forks = NULL;
}

void	destroy_global_mutexes(t_config *config)
{
	pthread_mutex_destroy(&config->print_mutex);
	pthread_mutex_destroy(&config->end_mutex);
}


/*void	free_threads(t_config *config)
{
	if (config->threads)
		free(config->threads);
	config->threads = NULL;
}*/

void	free_all(t_config *config)
{
	free_philosophers(config);
	free_forks(config);
	//free_threads(config);
	destroy_global_mutexes(config);
}
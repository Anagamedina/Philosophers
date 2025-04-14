#include "../include/philo.h"

int ft_limits_args(char *str, int i)
{
	long long nbr;

	nbr = ft_atoi(str);
	if (i == 1 && (nbr <= 0 || nbr > PHILO_LIMITATION))
		return (1);
	if (i >= 2 && i <= 4)
	{
		if (nbr <= 0 || nbr > INT_MAX)
			return (1);
	}
	if (i == 5 && (nbr > INT_MAX || nbr < 0))
		return (1);
	return (0);
}

int	check_argument_limits(int ac, char **av)
{
	if (ft_limits_args(av[1], 1)
		|| ft_limits_args(av[2], 2)
		|| ft_limits_args(av[3], 3)
		|| ft_limits_args(av[4], 4)
		|| (ac == 6 && ft_limits_args(av[5], 5)))
		return (1);
	return (0);
}

int is_valid_arguments(int ac, char **av)
{
	if ((ac != 5 && ac != 6) || ft_strdigit(av, 1, ac - 1))
		return (0);
	return (1);
}

int set_eat_limit(t_config *config, int ac, char **av)
{
	if (ac == 6)
	{
		config->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		if (config->number_of_times_each_philosopher_must_eat <= 0)
			return (1);
		config->is_limited = 1;
	}
	else
	{
		config->number_of_times_each_philosopher_must_eat = -1;
		config->is_limited = 0;
	}
	return (0);
}

int init_config(int ac, char **av, t_config *config)
{
	if (!is_valid_arguments(ac, av))
	{
		printf("Error: Incorrect number of arguments\n");
		return (1);
	}
	if (check_argument_limits(ac, av))
		return (1);
	config->number_of_philosophers = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);

	if (set_eat_limit(config, ac, av))
		return (1);

	if (config->number_of_philosophers <= 0 || config->time_to_die <= 0 ||
		config->time_to_eat <= 0 || config->time_to_sleep <= 0)
		return (1);

	config->simulation_over = -1;
	config->philos = malloc(sizeof(t_philos) * config->number_of_philosophers);
	config->threads = malloc(sizeof(pthread_t) * config->number_of_philosophers);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:26:02 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/02 19:09:18 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Función que valida los límites de los argumentos
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


// Función de inicialización de configuración
int init_config(int ac, char **av, t_config *config)
{
    if ((ac == 5 || ac == 6) && !ft_strdigit(av, 1, ac - 1))
    {
    	//check_valid_limits_args return(error)
        config->number_of_philosophers = ft_atoi(av[1]);
        config->time_to_die = ft_atoi(av[2]);
        config->time_to_eat = ft_atoi(av[3]);
        config->time_to_sleep = ft_atoi(av[4]);
        if (ac == 6)
        {
            config->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
            if (config->number_of_times_each_philosopher_must_eat <= 0)
            {
                printf("Error: They can't eat 0 or negative times\n");
                return (1);
            }
            config->is_limited = 1;
        }
        else
        {
            config->number_of_times_each_philosopher_must_eat = -1;
            config->is_limited = 0;
        }
        if (config->number_of_philosophers <= 0 || config->time_to_die <= 0 ||
            config->time_to_eat <= 0 || config->time_to_sleep <= 0)
        {
            printf("Error: Arguments must be positive numbers\n");
            return (1);
        }
    	config->simulation_over = -1;
    	config->philos= malloc(sizeof(t_philos) * config->number_of_philosophers);
    	config->threads = malloc(sizeof(pthread_t) * config->number_of_philosophers);

    }
	else
	{
		printf("Error: Incorrect number of arguments\n");
		return (1);
	}
	return (0);
}

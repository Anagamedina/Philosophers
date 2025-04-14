/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:05:22 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/02 17:55:43 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void print_fork_taken(t_philos *philo, char* str_fork)
{
	t_config *config = philo->config;

	pthread_mutex_lock(&philo->config->print_mutex);
	printf(BLUE "%d %d  %s \n"  RESET, get_time_in_ms() - config->simulation_time
, philo->id, str_fork);
	pthread_mutex_unlock(&philo->config->print_mutex);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// Función que valida que los argumentos sean dígitos
int ft_strdigit(char **av, int i, int j)
{
    while (av[j])
    {
        while (av[j][i])
        {
            if (av[j][i] < '0' || av[j][i] > '9' || ft_strlen(av[j]) > 10)
                return (1);
            i++;
        }
        i = 0;
        j++;
    }
    return (0);
}

int ft_atoi(const char* str)
{
    int             i;
    unsigned long long nbr;
    int             flag;

    i = 0;
    nbr = 0;
    flag = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        flag = 1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    if (flag == 1)
        nbr = -nbr;
    return (nbr);
}



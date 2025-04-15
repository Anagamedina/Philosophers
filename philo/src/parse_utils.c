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

void	print_action_color(t_philos *philo, const char *action, const char *color)
{
	t_config *config = philo->config;

	if (is_simulation_over(config))
		return ;

	pthread_mutex_lock(&config->print_mutex);
	if (!is_simulation_over(config))
	{
		unsigned long timestamp = get_time_in_ms() - config->simulation_time;
		printf("%s%lu %d %s%s\n",
			color,
			timestamp,
			philo->id,
			action,
			RESET);
	}
	pthread_mutex_unlock(&config->print_mutex);
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

unsigned long ft_atoi(const char* str)
{
    int             i;
    unsigned  long nbr;
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



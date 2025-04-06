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



void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, sizeof(char) * ft_strlen(s));
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

// Función para convertir una cadena a número
int ft_atoi(const char* str)
{
    int             i;
    unsigned long long nbr;
    int             flag;

    i = 0;
    nbr = 0;
    flag = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')  // Espacios y saltos de línea
        i++;
    if (str[i] == '+')  // Ignorar signo +
        i++;
    else if (str[i] == '-')  // Si es negativo
    {
        flag = 1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')  // Convertir los caracteres en número
    {
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    if (flag == 1)
        nbr = -nbr;  // Hacer el número negativo si corresponde
    return (nbr);
}



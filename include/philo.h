/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:57:20 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/02 18:05:04 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define PHILO_LIMITATION 200 // Limite de filósofos (puedes cambiarlo)

# define BLUE "\033[34m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"
#define RED "\033[31m"
// Estructura para almacenar los parámetros de los filósofos
typedef struct s_philos
{
    int number_of_philosophers;    // Número de filósofos
    int time_to_die;               // Tiempo máximo para que un filósofo muera
    int time_to_eat;               // Tiempo que un filósofo pasa comiendo
    int time_to_sleep;             // Tiempo que un filósofo pasa durmiendo
    int number_of_times_each_philosopher_must_eat;  // Número de veces que cada filósofo debe comer
    int is_limited;                // Si la comida está limitada o no
} t_philos;

// Prototipos de funciones
int init_philos(int ac, char **av, t_philos *philos);
int ft_strdigit(char **av, int i, int j);
long long ft_atoi(const char *str);
int ft_limits_args(char *str, int i);
size_t	ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);

// Funciones de simulación
void philo_thinks(int id);
void philo_eats(int id);
void philo_sleeps(int id);
void philo_die(int id);

#endif


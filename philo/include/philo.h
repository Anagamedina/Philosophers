/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:57:20 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/10 15:31:22 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

#define PHILO_LIMITATION 200 // Limite de filósofos (puedes cambiarlo)
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define RED "\033[31m"
typedef struct s_philos
{
    int id; 
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
    int last_meal_time;              
    int meals_eaten;
	struct s_config *config;               
    pthread_t thread_id;               
    pthread_mutex_t *left_fork;        
    pthread_mutex_t *right_fork;
	pthread_mutex_t meal_mutex;
} t_philos;

typedef struct s_config
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
    int meals_eaten;
	int number_of_times_each_philosopher_must_eat;
	int is_limited;
	int full_philosophers;      
	int simulation_over;
	int simulation_time;
	struct s_philos	*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t print_mutex;
	pthread_mutex_t end_mutex;
} t_config;



int init_config(int ac, char **av, t_config *config);
int ft_strdigit(char **av, int i, int j);
int ft_atoi(const char* str);
int ft_limits_args(char *str, int i);
size_t ft_strlen(char *s);
void ft_putstr_fd(char *s, int fd);

// Funciones de mulación
void philo_thinks(int id, t_config *config);
void philo_eats(t_philos *philo);
void philo_sleeps(int id, t_config *config);
void philo_die(int id, t_config *config);

// Funciones de hilos
void *philosopher_routine(void *arg);
void init_philosophers(t_config *config);
void init_mutex(t_config *config);
int create_threads(t_config* config);
void *philosopher_routine(void *arg);
int	get_time_in_ms(void);
void ft_usleep(int time_ms);
void *monitor_philos(void *arg);
void print_fork_taken(t_philos *philo);

int	create_monitor(t_config *config);
#endif


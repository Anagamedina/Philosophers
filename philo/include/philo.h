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

# define PHILO_LIMITATION 200 // Limite de filósofos (puedes cambiarlo)
#define RESET   "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"
#define YELLOW  "\033[0;33m"
#define CYAN    "\033[0;36m"
#define MAGENTA "\033[0;35m"

typedef struct s_philos
{
	int id;
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	unsigned long death_timer;
	int	is_full;
	int meals_eaten;
	struct s_config *config;
	pthread_t thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t deadline_to_eat;
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
	unsigned long simulation_time;
	struct s_philos	*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t print_mutex;
	pthread_mutex_t end_mutex;
} t_config;


int init_config(int ac, char **av, t_config *config);
int ft_strdigit(char **av, int i, int j);
unsigned long ft_atoi(const char* str);
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
void *monitor_philos(void *arg);
unsigned long get_time_in_ms(void);
void ft_usleep(unsigned long time_ms);
int	is_simulation_over(t_config *config);
int	create_monitor(t_config *config);
int set_eat_limit(t_config *config, int ac, char **av);
int is_valid_arguments(int ac, char **av);
int	check_argument_limits(int ac, char **av);
int	check_full_and_stop(t_philos *philo);
void	take_forks(t_philos *philo);
int	handle_one_philosopher(t_philos *philo);
void	free_all(t_config *config);
void	release_forks(t_philos *philo);
void	print_action_color(t_philos *philo, const char *action, const char *color);


#endif


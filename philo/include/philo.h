/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:57:20 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/21 20:58:43 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define RESET   "\033[0m"
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define BLUE    "\033[0;34m"
# define YELLOW  "\033[0;33m"
# define CYAN    "\033[0;36m"
# define MAGENTA "\033[0;35m"

typedef struct s_philos
{
	int				id;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	unsigned long	death_timer;
	int				is_full;
	int				meals_eaten;
	struct s_config	*config;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	deadline_to_eat;
}			t_philos;

typedef struct s_config
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_eaten;
	int				max_meals;
	int				is_limited;
	int				full_philosophers;
	int				simulation_over;
	unsigned long	simulation_time;
	t_philos		*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
}		t_config;

// parsing.c
int					init_config(int ac, char **av, t_config *config);
int					ft_strdigit(char **av, int i, int j);
unsigned long		ft_atoi(const char *str);
int					ft_limits_args(char *str, int i);
size_t				ft_strlen(char *s);
int					set_eat_limit(t_config *config, int ac, char **av);
int					is_valid_arguments(int ac, char **av);

// time.c
unsigned long		get_time_in_ms(void);
void				ft_usleep(unsigned long time_ms);
void				philo_sleep_and_think(t_philos *philo);

// philosopher.c
void				*philosopher_routine(void *arg);
int					handle_one_philosopher(t_philos *philo);
int					check_full_and_stop(t_philos *philo);
void				release_forks(t_philos *philo);

// actions.c
void				print_action_color(t_philos *philo, \
		const char *action, const char *color);

// state..c
int					philo_take_forks(t_philos *philo);
void				philo_eat(t_philos *philo);
void				philo_die(int id, t_config *config);

// init.c
void				init_philosophers(t_config *config);
void				init_mutex(t_config *config);
int					create_threads(t_config *config);

// monitor.c
int					is_simulation_over(t_config *config);
int					create_monitor(t_config *config);
void				safe_end_simulation(t_config *config, int id);

// cleanup.c
void				free_all(t_config *config);
void				destroy_global_mutexes(t_config *config);
void				free_philosophers(t_config *config);
void				free_forks(t_config *config);

#endif

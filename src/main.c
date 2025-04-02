/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:52:31 by anamedin          #+#    #+#             */
/*   Updated: 2025/04/02 18:04:44 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void philo_thinks(int id) {
    printf(BLUE "Philosopher %d is thinking\n" RESET, id);
}

void philo_eats(int id) {
    printf(GREEN "Philosopher %d is eating\n" RESET, id);
}

void philo_sleeps(int id) {
    printf(YELLOW "Philosopher %d is sleeping\n" RESET, id);
}

void philo_die(int id)
{
    printf(RED "El filósofo %d ha muerto\n" RESET, id);
}

	
int main(int ac, char **av)
{
    t_philos philos;

    if (init_philos(ac, av, &philos) == 0)
    {
        printf("Initialization successful!\n");
        printf("Number of Philosophers: %d\n", philos.number_of_philosophers);
        printf("Time to Die: %d\n", philos.time_to_die);
        printf("Time to Eat: %d\n", philos.time_to_eat);
        printf("Time to Sleep: %d\n", philos.time_to_sleep);
        if (philos.is_limited)
            printf("Number of Times Each Philosopher Must Eat: %d\n", philos.number_of_times_each_philosopher_must_eat);
        else
            printf("Unlimited eating.\n");

		  // Simulación de la rutina de los filósofos (con colores)
        philo_thinks(1);
        philo_eats(1);
        philo_sleeps(1);
		philo_die(1);
    }
    else
        printf("Initialization failed.\n");

    return (0);
}
   

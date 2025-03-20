
/*

1. Para ejecutar-->  ./philo number_of_philo time_to_die time_to_eat time_to_sleep

- number_of_philosophers: es el número de filósofos, pero también el número
de tenedores.
- time_to_die (en milisegundos): si un filósofo no empieza a comer en time_to_die
milisegundos desde el comienzo de su ultima comida o desde el principio de la
simulación, este morirá.
- time_to_eat (en milisegundos): es el tiempo que tiene un filósofo para comer.
Durante ese tiempo, tendrá los tenedores ocupados.
- time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo para dormir.
- number_of_times_each_philosopher_must_eat (argumento opcional): si todos los filósofos comen al menos number_of_times_each_philosopher_must_eat
veces, la simulación se detendrá. Si no se especifica, la simulación se detendrá
con la muerte de un filósofo.

2.Cada filósofo tendrá asignado un número del 1 al number_of_philosophers

3. Cada filósofo debe comer time_to_eat milisegundos, dormir time_to_sleep
milisegundos y pensar time_to_think milisegundos
El filósofo número 1 se sentará al lado del filósofo número number_of_philosophers.
Cualquier otro filósofo número N se sentarán entre el filósofo número N - 1 y el filósofo
número N + 1.
*/
int main(int argc, char **argv)
{
    //t_philo *philo;
    //t_philo **philo_tab;
    int i;

    if (argc != 5)
        return (printf("Error: bad arguments\n"), 1);
}     

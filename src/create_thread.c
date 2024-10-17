#include "../include/h_philo.h"

void    *action_philo(void *arg)
{
    t_philo *philos;

    philos = (t_philo *)arg;
    while (1)
    {
        eating(philos);
        sleeping(philos);
        thinking(philos);
        monitor(philos);
    }
}

int    create_thread(t_program program, t_philo *philos)
{
    int i;

    i = 0;
    while (i < program.num_of_philos)
    {
        if (pthread_create(&philos->thread, NULL, action_philo, &philos[i]) == -1)
            return (false);
        i++;
    }
    pthread_join(philos->thread, NULL);
    return 0;
}

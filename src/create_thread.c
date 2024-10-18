#include "../include/h_philo.h"

void    *action_philo(void *_philo)
{
    t_philo *philo;

    philo = (t_philo *)_philo;
    while (1)
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
        if (monitor(philo) == NULL)
            break ;
    }
    return NULL;
}

int    create_thread(t_program program, t_philo *philos)
{
    int i;

    i = 0;
    while (i < program.num_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, action_philo, &philos[i]) != 0)
            return (1);
        if (pthread_join(philos[i].thread, NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}

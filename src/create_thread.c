#include "../include/h_philo.h"

void    *monitor(void *_philo)
{
    t_philo *philo;
    size_t  current_date;

    philo = (t_philo *)_philo;
    current_date = get_current_time();
    while (1)
    {
        if (philo->time_to_die < (current_date - philo->start_time))
            return (print_message(philo, "is died"), NULL);
        if (philo->num_times_to_eat < philo->meal_count)
            return (print_message(philo, "is died"), NULL);
    }
    return (philo);
}

void    *action_philo(void *_philo)
{
    t_philo *philo;

    philo = (t_philo *)_philo;
    while (1)
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return NULL;
}

int    create_thread(t_program program, t_philo *philos)
{
    int i;
    pthread_t _monitor;

    i = 0;
	_monitor = (pthread_t)malloc(sizeof(pthread_t));
	if (!_monitor)
		return (write(1, "Malloc Error\n", 13), false);
    while (i < program.num_of_philos)
    {
		ft_usleep(300);
        if (pthread_create(&philos[i].thread, NULL, action_philo, &philos[i]) != 0)
        {
            while (i > 0)
                pthread_detach(philos[i--].thread);
            return (write(2, "Pthread_create Error\n", 21), false);
        }
        i++;
    }

    if (pthread_create(&_monitor, NULL, monitor, philos) != 0)
        return (write(2, "Pthread_create Error\n", 21), false);
    i = 0;
    while (i > 0)
    {
        if (pthread_join(philos[i].thread, NULL) != 0)
            return (1);
        i--;
    }
    return (0);
}


#include "../include/h_philo.h"


int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mtx);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(philo->death_mtx), 1);
	pthread_mutex_unlock(philo->death_mtx);
	return (0);
}

void    *action_philo(void *_philo)
{
    t_philo *philo;

    philo = (t_philo *)_philo;
    while (!dead_loop(philo))
    {
		if (philo->is_dead)
			break;
        eating(philo);
		if (philo->is_dead)
			break;
        sleeping(philo);
		if (philo->is_dead)
			break;
        thinking(philo);
		if (philo->is_dead)
			break;
    }
    return NULL;
}

int    create_thread(t_program program, t_philo *philos)
{
    int i;
    pthread_t _monitor;

    i = 0;
    if (pthread_create(&_monitor, NULL, monitor, philos) != 0)
		return (write(STDERR_FILENO, "Pthread_create Error\n", 21), false);
    while (i < program.num_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, action_philo, &philos[i]) != 0)
        {
            while (i > 0)
                pthread_detach(philos[i--].thread);
            return (write(STDERR_FILENO, "Pthread_create Error\n", 21), false);
        }
        i++;
    }
	if (pthread_join(_monitor, NULL) != 0)
		return (1);
	i = 0;
    while (i < program.num_of_philos)
    {
        if (pthread_join(philos[i++].thread, NULL) != 0)
            return (1);
    }
    return (0);
}


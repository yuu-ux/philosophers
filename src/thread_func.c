#include "../include/h_philo.h"
#include <pthread.h>

void    print_message(t_philo *philo, char *message)
{
    long current_date;

    current_date = philo->last_time - philo->start_time;
    printf("%ld %d %s\n", current_date, philo->id, message);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork);
    print_message(philo, "has taken a fork");
    pthread_mutex_lock(&philo->right_fork);
    print_message(philo, "has taken a fork");
    print_message(philo, "is eating");
    pthread_mutex_lock(philo->write_mtx);
    philo->last_time = get_current_time();
    philo->meal_count++;
    pthread_mutex_unlock(philo->write_mtx);
    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(&philo->right_fork);
}

void    sleeping(t_philo *philo)
{
    print_message(philo, "is sleeping");
}

void    thinking(t_philo *philo)
{
    print_message(philo, "is thinking");
}

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
    return philo;
}

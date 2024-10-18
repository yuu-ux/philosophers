#include "../include/h_philo.h"

void    print_message(t_philo *philo, char *message)
{
    long current_date;

    current_date = philo->last_time - philo->start_time;
    printf("%ld %d %s\n", current_date, philo->id, message);
}

void    eating(t_philo *philo)
{
    print_message(philo, "is eating");
    philo->last_time = get_current_time();
}

void    sleeping(t_philo *philo)
{
    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(&philo->right_fork);
    print_message(philo, "is sleeping");
}

void    thinking(t_philo *philo)
{
    print_message(philo, "is thinking");
    pthread_mutex_lock(&philo->left_fork);
    print_message(philo, "has taken a fork");
    pthread_mutex_lock(&philo->right_fork);
    print_message(philo, "has taken a fork");
}

void    *monitor(void *_philo)
{
    t_philo *philo;
    size_t  current_time;

    philo = (t_philo *)_philo;
    current_time = get_current_time();
    if (philo->time_to_die < (current_time - philo->start_time))
    {
        print_message(philo, "is died");
        return NULL;
    }
    return philo;
}

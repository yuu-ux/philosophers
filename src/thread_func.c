#include "../include/h_philo.h"

void    print_message(t_philo *philo, char *message)
{
    long current_date;

    current_date = philo->last_meal_time - philo->start_time;
    printf("%ld %d %s\n", current_date, philo->id, message);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork);
    pthread_mutex_lock(&philo->right_fork);
    print_message(philo, "has taken a fork");
    print_message(philo, "is eating");
    philo->last_meal_time = get_current_time();
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

void    *monitor(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->status == DIE)
    {
        print_message(philo, "is died");
        return NULL;
    }
    return NULL;
}

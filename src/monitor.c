#include "../include/h_philo.h"

int is_philo_dead(t_philo *philo)
{
    pthread_mutex_lock(philo->meal_mtx);
    if (philo->time_to_die <= (current_date - philo->last_time))
    {
        philo->is_dead = 1;
        print_message(philo, "is died");
        return NULL;
    }

}

void    *monitor(void *_philo)
{
    t_philo *philo;
    size_t  current_date;

    philo = (t_philo *)_philo;
    current_date = get_current_time();
    while (1)
    {
        if (philo->num_times_to_eat < philo->meal_count)
            return (philo->is_dead = 1, NULL);
    }
    return philo;
}

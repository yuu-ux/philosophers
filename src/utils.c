#include "../include/h_philo.h"

size_t  get_current_time()
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        return -1;
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    all_destory(t_program *program, t_philo *philos)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&program[i].think_mtx);
    pthread_mutex_destroy(&program[i].meal_mtx);
    pthread_mutex_destroy(&program[i].death_mtx);
    while (i < program->num_of_philos)
    {
        pthread_mutex_destroy(&philos[i].left_fork);
        pthread_mutex_destroy(&philos[i].right_fork);
        i++;
    }
}

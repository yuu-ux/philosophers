#include "../include/h_philo.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' ||
           c == '\v' || c == '\f' ||
           c == '\r' || c == ' ');
}

size_t	get_current_time()
{
    struct timeval	time;

    if (gettimeofday(&time, NULL) == -1)
        return (-1);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t msec)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < msec)
		usleep(500);
	return (0);
}

void	destroy_all(t_philo *philos, t_mtx *forks)
{
	int	i;

	i = 0;
    pthread_mutex_destroy(philos->write_mtx);
    pthread_mutex_destroy(philos->meal_mtx);
    pthread_mutex_destroy(philos->death_mtx);
    while (i < philos->num_of_philos)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
	free(philos);
}


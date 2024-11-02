#include "../include/h_philo.h"

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_mtx);
		if (philos[i].meal_count >= philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_mtx);
		i++;
	}
	if (finished_eating == philos[0].num_times_to_eat)
	{
		pthread_mutex_lock(philos[0].death_mtx);
		philos->is_dead = 1;
		pthread_mutex_unlock(philos[0].death_mtx);
		return (1);
	}
	return (0);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->write_mtx);
	if ((get_current_time() - philo->last_time) >= time_to_die)
		return (pthread_mutex_unlock(philo->meal_mtx), 1);
	pthread_mutex_unlock(philo->write_mtx);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_message(&philos[i], "died");
			pthread_mutex_lock(philos[0].death_mtx);
			philos->is_dead = 1;
			pthread_mutex_unlock(philos[0].death_mtx);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *_philos)
{
    t_philo *philos;

    philos = (t_philo *)_philos;

    while (1)
    {
		if (check_if_dead(philos) == 1) // || check_if_all_ate(philos) == 1
			break ;
    }
    return (philos);
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
		pthread_mutex_lock(philo->death_mtx);
		if (philo->is_dead)
			break ;
		pthread_mutex_unlock(philo->death_mtx);
    }
    return NULL;
}

int    create_thread(t_program program, t_philo *philos)
{
    int i;
    pthread_t _monitor;

    i = 0;
	(void)program;
    if (pthread_create(&_monitor, NULL, monitor, philos) != 0)
		return (write(STDERR_FILENO, "Pthread_create Error\n", 21), false);
    while (i < program.num_of_philos)
    {
		ft_usleep(300);
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
        if (pthread_join(philos[i].thread, NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}


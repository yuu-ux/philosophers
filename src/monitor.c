/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:13:58 by yehara            #+#    #+#             */
/*   Updated: 2024/11/03 17:14:00 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/h_philo.h"

int	check_if_all_ate(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].write_mtx);
		if (philos[i].meal_count >= philos[i].num_times_to_eat)
			philos[i++].is_eaten = true;
		pthread_mutex_unlock(philos[0].write_mtx);
	}
	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].write_mtx);
		if (philos[i++].is_eaten == false)
			return (pthread_mutex_unlock(philos[0].write_mtx), 0);
		pthread_mutex_unlock(philos[0].write_mtx);
	}
	pthread_mutex_lock(philos[0].death_mtx);
	*(philos[0].is_dead) = true;
	pthread_mutex_unlock(philos[0].death_mtx);
	return (1);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->write_mtx);
	if ((get_current_time() - philo->meal_start_time) >= time_to_die)
		return (pthread_mutex_unlock(philo->write_mtx), 1);
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
			*(philos[0].is_dead) = true;
			pthread_mutex_unlock(philos[0].death_mtx);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *_philos)
{
	t_philo	*philos;

	philos = (t_philo *)_philos;
	while (1)
	{
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	}
	return (philos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:13:52 by yehara            #+#    #+#             */
/*   Updated: 2024/11/03 17:13:54 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/h_philo.h"

void	print_message(t_philo *philo, char *message)
{
	printf("%ld %d %s\n", (get_current_time() - philo->start_time), philo->id,
		message);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_message(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
	{
		*(philo->is_dead) = 1;
		return ;
	}
	pthread_mutex_lock(&philo->right_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(philo->write_mtx);
	philo->start_time = get_current_time();
	philo->meal_count++;
	pthread_mutex_unlock(philo->write_mtx);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

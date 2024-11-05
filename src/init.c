/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:14:10 by yehara            #+#    #+#             */
/*   Updated: 2024/11/03 17:14:12 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/h_philo.h"

int	alloc_philos_forks(t_program program, t_philo **philos, t_mtx **forks)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * program.num_of_philos);
	if (!(*philos))
		return (write(STDERR_FILENO, "Malloc Error\n", 13), 1);
	*forks = (t_mtx *)malloc(sizeof(t_mtx) * program.num_of_philos);
	if (!(*forks))
		return (write(STDERR_FILENO, "Malloc Error\n", 13), 1);
	return (0);
}

int	init_fork(t_program program, t_mtx *forks)
{
	int	i;

	i = 0;
	while (i < program.num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (write(STDERR_FILENO, "Mutex Error\n", 12), 1);
		i++;
	}
	return (0);
}

void	input_data(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atol(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_program *program, t_philo *philos, t_mtx *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		philos[i].id = i + 1;
		input_data(&philos[i], argv);
		philos[i].meal_count = 0;
		philos[i].start_time = get_current_time();
		philos[i].meal_start_time = get_current_time();
		philos[i].is_dead = &program->is_dead;
		philos[i].is_eaten = false;
		philos[i].right_fork = &forks[i];
		philos[i].write_mtx = &program->write_mtx;
		philos[i].death_mtx = &program->death_mtx;
		if (i == 0)
			philos[i].left_fork = &forks[program->num_of_philos - 1];
		else
			philos[i].left_fork = &forks[i - 1];
		i++;
	}
}

int	init_program(t_program *program, t_philo **philos, t_mtx **forks,
		char **argv)
{
	program->num_of_philos = ft_atol(argv[1]);
	program->is_dead = false;
	if (alloc_philos_forks(*program, philos, forks))
		return (1);
	if (init_fork(*program, *forks))
		return (1);
	init_philos(program, *philos, *forks, argv);
	if (pthread_mutex_init(&program->write_mtx, NULL) != 0)
		return (write(STDERR_FILENO, "Mutex Error\n", 12), 1);
	if (pthread_mutex_init(&program->death_mtx, NULL) != 0)
		return (write(STDERR_FILENO, "Mutex Error\n", 12), 1);
	program->philos = *philos;
	return (0);
}

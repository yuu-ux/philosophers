/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:13:32 by yehara            #+#    #+#             */
/*   Updated: 2024/11/03 17:13:35 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/h_philo.h"

int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}

int	validate_arg(char **argv)
{
	int	must_eat_num;

	if (ft_isdigit(argv[1]) || ft_atol(argv[1]) > MAX_PHILO)
		return (write(STDERR_FILENO, "error: num_of_philo\n", 20), 1);
	else if (ft_isdigit(argv[2]) || ft_atol(argv[2]) < MIN_TIME)
		return (write(STDERR_FILENO, "error: time_to_die\n", 19), 1);
	else if (ft_isdigit(argv[3]) || ft_atol(argv[3]) < MIN_TIME)
		return (write(STDERR_FILENO, "error: time_to_eat\n", 20), 1);
	else if (ft_isdigit(argv[4]) || ft_atol(argv[4]) < MIN_TIME)
		return (write(STDERR_FILENO, "error: time_to_sleep\n", 22), 1);
	else if (argv[5])
	{
		must_eat_num = ft_atol(argv[5]);
		if (must_eat_num < 0)
			return (write(STDERR_FILENO, "error: must_eat_num\n", 21), 1);
	}
	return (0);
}

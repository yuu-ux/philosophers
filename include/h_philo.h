/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:25:10 by yehara            #+#    #+#             */
/*   Updated: 2024/11/04 22:25:12 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_PHILO_H
# define H_PHILO_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200
# define MIN_TIME 60

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					num_times_to_eat;
	int					meal_count;
	size_t				start_time;
	size_t				meal_start_time;
	bool				*is_dead;
	bool				is_eaten;
	t_mtx				*left_fork;
	t_mtx				*right_fork;
	t_mtx				*write_mtx;
	t_mtx				*death_mtx;
	int					num_of_philos;
}						t_philo;

typedef struct s_program
{
	bool				is_dead;
	t_mtx				write_mtx;
	t_mtx				death_mtx;
	int					num_of_philos;
	t_philo				*philos;
}						t_program;

// main.c
long					ft_atol(char *str);

// validate.c
int						validate_arg(char **argv);

// init.c
bool					init_program(t_program *program, t_philo **philos,
							t_mtx **forks, char **argv);
void					init_philos(t_program *program, t_philo *philos,
							t_mtx *forks, char **argv);

// utils.c
size_t					get_current_time(void);
int						ft_isspace(int c);
void					destroy_all(t_philo *philos, t_mtx *forks);
int						ft_usleep(size_t msec);

// create_thread.c
int						create_thread(t_program program, t_philo *philos);
void					*action_philo(void *_philo);

// thread_func.c
void					print_message(t_philo *philo, char *message);
void					eating(t_philo *philos);
void					sleeping(t_philo *philos);
void					thinking(t_philo *philos);

// monitor.c
int						check_if_all_ate(t_philo *philos);
int						philosopher_dead(t_philo *philo, size_t time_to_die);
int						check_if_dead(t_philo *philos);
void					*monitor(void *_philos);

#endif

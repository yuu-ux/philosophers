#include "../include/h_philo.h"

void    init_fork(t_program program, t_philo *philos)
{
    int i;

    i = 0;
    while (i < program.num_of_philos)
    {
        pthread_mutex_init(&philos[i].left_fork, NULL);
        pthread_mutex_init(&philos[i].right_fork, NULL);
        i++;
    }
}

void    init_philos(t_program program, t_philo *philos, char **argv)
{
    int i;

    i = 0;
    while (i < program.num_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].time_to_die = ft_atol(argv[2]);
        philos[i].time_to_eat = ft_atol(argv[3]);
        philos[i].time_to_sleep = ft_atol(argv[4]);
        philos[i].last_time = get_current_time();
        philos[i].start_time = get_current_time();
        philos[i].is_dead = false;
        if (argv[5])
            philos[i].num_times_to_eat = ft_atol(argv[5]);
        i++;
    }
}

void    init_program(t_program *program, t_philo *philos, char **argv)
{
    program->num_of_philos = ft_atol(argv[1]);
    init_philos(*program, philos, argv);
    init_fork(*program, philos);
    program->philos = philos;
    pthread_mutex_init(&program->think_mtx, NULL);
    pthread_mutex_init(&program->meal_mtx, NULL);
    pthread_mutex_init(&program->death_mtx, NULL);
}

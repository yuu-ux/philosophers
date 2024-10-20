#include "../include/h_philo.h"

bool    init_fork(t_program program, t_mtx *forks)
{
    int i;

    i = 0;
    while (i < program.num_of_philos)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
            return (write(2, "Mutex Error\n", 12), false);
        i++;
    }
    return (true);
}

void    init_philos(t_program *program, t_philo *philos, t_mtx *forks, char **argv)
{
    int i;

    i = 0;
    while (i < program->num_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].time_to_die = ft_atol(argv[2]);
        philos[i].time_to_eat = ft_atol(argv[3]);
        philos[i].time_to_sleep = ft_atol(argv[4]);
        philos[i].meal_count = 0;
        philos[i].last_time = get_current_time();
        philos[i].start_time = get_current_time();
        philos[i].is_dead = false;
        philos[i].right_fork = forks[i];
        philos[i].write_mtx = &program->write_mtx;
        philos[i].meal_mtx  = &program->meal_mtx;
        philos[i].death_mtx = &program->death_mtx;
        if (i == 0)
            philos[i].left_fork = forks[program->num_of_philos - 1];
        else
            philos[i].left_fork = forks[i - 1];
        if (argv[5])
            philos[i].num_times_to_eat = ft_atol(argv[5]);
        i++;
    }
}

bool    init_program(t_program *program, t_philo *philos, t_mtx *forks, char **argv)
{
    program->num_of_philos = ft_atol(argv[1]);
    if (!init_fork(*program, forks))
        return (false);
    init_philos(program, philos, forks, argv);
    if (pthread_mutex_init(&program->write_mtx, NULL) != 0)
        return (write(2, "Mutex Error\n", 12), false);
    if (pthread_mutex_init(&program->meal_mtx, NULL) != 0)
        return (write(2, "Mutex Error\n", 12), false);
    if (pthread_mutex_init(&program->death_mtx, NULL) != 0)
        return (write(2, "Mutex Error\n", 12), false);
    program->philos = philos;
    return (true);
}

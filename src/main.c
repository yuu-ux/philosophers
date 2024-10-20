#include "../include/h_philo.h"

long    ft_atol(char *str)
{
    long    ret;
    int     sign;

    ret = 0;
    sign = 1;
    if (!str)
        return (-1);
    while (*str == '\t' || *str == '\n' ||
           *str == '\v' || *str == '\f' ||
           *str == '\r' || *str == ' ')
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str)
    {
        if ((ret > LONG_MAX / 10) || (ret == LONG_MAX / 10 && *str > '7'))
            return (LONG_MAX);
        else if ((ret < LONG_MIN / 10) || (ret == LONG_MIN / 10 && *str > '8'))
            return (LONG_MIN);
        ret = ret * 10 + (*str - '0') * sign;
        str++;
    }
    return (ret);
}

int main(int argc, char **argv)
{
    t_program   program;
    t_philo     *philos;
    t_mtx       *forks;

    if (!(argc == 5 || argc == 6))
    {
        write(2, "usage: 5 900 300 300 5\n", 23);
        return (1);
    }
    else
    {
        philos = (t_philo *)malloc(sizeof(t_philo) * program.num_of_philos);
        if (!philos)
            return (write(2, "Malloc Error\n", 13), 1);
        forks = (t_mtx *)malloc(sizeof(t_mtx) * program.num_of_philos);
        if (!forks)
            return (write(2, "Malloc Error\n", 13), 1);
        if (validate_arg(argv) == 1)
            return (1);
        init_program(&program, philos, forks, argv);
        create_thread(program, philos);
        //destory_all();
    }
    return (0);
}

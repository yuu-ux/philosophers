#include "../include/h_philo.h"

long    ft_atol(char *str)
{
    long	ret;
    int		sign;

    ret = 0;
    sign = 1;
	errno = 0;
    if (!str)
        return ((errno = EINVAL), 1);
    while (ft_isspace(*str))
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*(str++) == '-')
            sign = -1;
    }
    while (*str)
    {
        if ((ret > LONG_MAX / 10) || (ret == LONG_MAX / 10 && *str > '7'))
            return (LONG_MAX);
        else if ((ret < LONG_MIN / 10) || (ret == LONG_MIN / 10 && *str > '8'))
            return (LONG_MIN);
        ret = ret * 10 + (*(str++) - '0') * sign;
    }
    return (ret);
}


int main(int argc, char **argv)
{
    t_program	program;
    t_philo		*philos = {0};
    t_mtx		*forks = {0};

	if (!(argc == 5 || argc == 6))
		return (write(2, "usage: 5 900 300 300 5\n", 23), 1);
	if (validate_arg(argv) == 1)
		return (1);
	if (!(init_program(&program, philos, forks, argv)))
		return (1);
		//return (destroy_all(philos, forks), 1);
	if (!(create_thread(program, philos)))
			return (1);
			//return (destroy_all(philos, forks), 1);
	// destroy_all(philos, forks);
    return (0);
}

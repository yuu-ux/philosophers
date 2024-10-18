#ifndef H_PHILO_H
# define H_PHILO_H
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX_PHILO 200
#define MIN_TIME 60
typedef pthread_mutex_t t_mtx;

enum STATUS {
    MEAL,
    SLEEP,
    DIE,
};

typedef struct s_philo {
    pthread_t   thread;
    int         id;
    int         status;
    size_t      time_to_die;
    size_t      time_to_eat;
    size_t      time_to_sleep;
    int         num_times_to_eat;
    int         meals_count;
    size_t      last_meal_time;
    size_t      start_time;
    bool        is_dead;
    t_mtx       left_fork;
    t_mtx       right_fork;
} t_philo;

typedef struct s_program {
    t_mtx   think_mtx;
    t_mtx   meal_mtx;
    t_mtx   death_mtx;
    int     num_of_philos;
    t_philo *philos;
} t_program;

// main.c
long    ft_atol(char *str);

// validate.c
int     validate_arg(char **argv);

// init.c
void    init_program(t_program *program, t_philo *philos, char **argv);
void    init_philos(t_program program, t_philo *philos, char **argv);

// utils.c
size_t  get_current_time();

// create_thread.c
int    create_thread(t_program program, t_philo *philos);
void *action_philo(void *arg);

// thread_func.c
void    eating(t_philo *philos);
void    sleeping(t_philo *philos);
void    thinking(t_philo *philos);
void    *monitor(void *arg);

#endif

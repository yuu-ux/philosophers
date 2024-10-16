#include "../include/h_philo.h"

size_t  get_current_time()
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        return -1;
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

#pragma once

#include <sys/time.h>
#include <cinttypes>

static timeval _start_millis_time;

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}


uint32_t get_millisecond_timer()
{
    if(_start_millis_time.tv_sec == 0)
    {
        gettimeofday(&_start_millis_time, NULL);
    }
    timeval current_time;
    gettimeofday(&current_time, NULL);

    timeval running_time;
    timeval_subtract(&running_time, &_start_millis_time, &current_time);

    return running_time.tv_sec * 1000 + running_time.tv_usec / 1000;
}

unsigned long millis()
{
    return get_millisecond_timer();
}

unsigned long micros()
{
    if(_start_millis_time.tv_sec == 0)
    {
        gettimeofday(&_start_millis_time, NULL);
    }
    timeval current_time;
    gettimeofday(&current_time, NULL);

    timeval running_time;
    timeval_subtract(&running_time, &_start_millis_time, &current_time);

    return running_time.tv_sec * 1000000 + running_time.tv_usec / 1000000;
}

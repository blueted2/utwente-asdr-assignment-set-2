#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

void *thread_routine() {
    // create array to hold mesured timing
    long long measurements[1000];

    // get current time
    struct timespec t_start;
    clock_gettime(CLOCK_REALTIME, &t_start);

    struct timespec t_running = t_start;

    // run for 1 second
    for (int i = 0; i < 1000; i++) {

        t_running.tv_nsec += 1000000;
        if (t_running.tv_nsec >= 1000000000) {
            t_running.tv_nsec -= 1000000000;
            t_running.tv_sec++;
        }
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &t_running, NULL);

        // get the time in nanoseconds since the start
        struct timespec t_now;
        clock_gettime(CLOCK_REALTIME, &t_now);

        struct timespec t_diff;
        t_diff.tv_sec = t_now.tv_sec - t_start.tv_sec;
        t_diff.tv_nsec = t_now.tv_nsec - t_start.tv_nsec;
        if (t_diff.tv_nsec < 0) {
            t_diff.tv_nsec += 1000000000;
            t_diff.tv_sec--;
        }

        // convert to nanoseconds
        measurements[i] = t_diff.tv_sec * 1000000000 + t_diff.tv_nsec;
    }

    // // calculate the average difference between measurements
    // long long sum_ns = measurements[0];
    // for (int i = 1; i < 1000; i++) {
    //     sum_ns += measurements[i] - measurements[i-1];
    // }
    // sum_ns /= 1000;

    // calculate the deltas between measurements
    long long deltas[999];
    for (int i = 0; i < 999; i++) {
        deltas[i] = measurements[i+1] - measurements[i];
    }

    // calculate the average delta
    long long average_ns = deltas[0];
    for (int i = 1; i < 999; i++) {
        average_ns += deltas[i];
    }

    average_ns /= 999;

    // standard deviation
    long long std_dev_ns = deltas[0] - average_ns;
    std_dev_ns *= std_dev_ns;
    for (int i = 1; i < 999; i++) {
        long long delta = deltas[i] - average_ns;
        std_dev_ns += delta * delta;
    }
    std_dev_ns /= 999;
    std_dev_ns = sqrt(std_dev_ns);


    // print the results
    printf("average: %lld ns\n", average_ns);
    printf("std_dev: %lld ns\n", std_dev_ns);


    // print deltas as a bar graph, with 20 '#' per ms
    for (int i = 0; i < 999; i++) {
        printf("%3d: ", i);
        for (int j = 0; j < deltas[i] / 50000; j++) {
            // print '|' at each 1 ms
            if (j % 20 == 0) {
                printf("|");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }


}

int main(void) {

    
    
    pthread_t thread_id;

    int res = pthread_create(
        &thread_id,
        NULL,
        thread_routine,
        NULL
    );

    if (res != 0) {
        perror("failed to create thread\n");
        exit(1);
    }
    pthread_join(thread_id, NULL);

    return 0;
}
// Kashmir Jmashaid 
// 23-NTU-CS-1167
// TASK-1
// Write a program that creates 5 threads. Each thread should:
// - Print its thread ID using `pthread_self()`.
// - Display its thread number (1st, 2nd, etc.).
// - Sleep for a random time between 1–3 seconds.
// - Print a completion message before exiting.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h> // For  srand(),time() and aslo rand()
// Thread function
void* thread_function(void* arg) {
    int thread_num = *(int*)arg; // Convert the passed argument to an integer (thread number)

    printf("Thread No: %d\n", thread_num);
    printf("Thread %d ID: %lu\n", thread_num, pthread_self());

    int sleep_time = (rand() % 3) + 1; // Sleep for random time between 1–3 seconds
    printf("Thread %d sleeping for %d seconds...\n", thread_num, sleep_time);
    sleep(sleep_time);

    printf("Thread %d completed!\n\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_nums[5];

    printf("Main thread starting...\n");
    printf("Main Thread ID: %lu\n\n", pthread_self());

    srand(time(NULL)); // Seed for random sleep times

    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        thread_nums[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed. Main thread exiting...\n");
    return 0;
}

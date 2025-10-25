#include <stdio.h>
#include <pthread.h>
#include <unistd.h>   // ✅ Needed for getpid()

#define NUM_THREADS 4 // preprocessor macro: number of threads to create (4).
int varg = 0;         // global integer (initialized to 0). All threads share this variable.

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;

    int varl = 0;
    varg++;
    varl++;
    printf("Thread %d is executing the global value is %d: local value is %d: process id %d\n",
           thread_id, varg, varl, getpid());
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Main is executing the global value is %d :: Process ID %d\n", varg, getpid());

    return 0;
}

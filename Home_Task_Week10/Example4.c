#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define WORKERS 3
#define TASKS 10

sem_t worker_sem;          // Controls worker availability

pthread_mutex_t mutex;     // For printing / tracking safely

void* task(void* arg) {
    int id = *(int*)arg;


    // Wait until a worker is free
    sem_wait(&worker_sem);

    pthread_mutex_lock(&mutex);
    printf("Task %d started by a worker.\n", id);
    pthread_mutex_unlock(&mutex);

    // Simulate task work
    int t = (rand() % 2) + 1;
    sleep(t);

    pthread_mutex_lock(&mutex);
    printf("Task %d finished.\n", id);
    pthread_mutex_unlock(&mutex);

    // Release worker
    sem_post(&worker_sem);

    return NULL;
}

int main() {
    pthread_t tasks[TASKS];
    int ids[TASKS];

    srand(time(NULL));

    // Initialize semaphore with 3 workers available
    sem_init(&worker_sem, 0, WORKERS);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create task threads
    for (int i = 0; i < TASKS; i++) {
        ids[i] = i + 1;
        pthread_create(&tasks[i], NULL, task, &ids[i]);
    }

    // Wait for all tasks to finish
    for (int i = 0; i < TASKS; i++) {
        pthread_join(tasks[i], NULL);
    }

    // Cleanup
    sem_destroy(&worker_sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
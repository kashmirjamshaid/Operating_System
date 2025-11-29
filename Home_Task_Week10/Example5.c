#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define STATIONS 2
#define CARS 8

sem_t wash_sem;              // Controls washing station availability
pthread_mutex_t mutex;       // Protects queue counter

int waiting = 0;             // queue length tracker

void* car(void* arg) {
    int id = *(int*)arg;


    // Car enters waiting queue
    pthread_mutex_lock(&mutex);
    waiting++;
    printf("Car %d is waiting. Queue length: %d\n", id, waiting);
    pthread_mutex_unlock(&mutex);

    // Wait for washing station
    sem_wait(&wash_sem);

    // Car gets a washing station → remove from queue
    pthread_mutex_lock(&mutex);
    waiting--;
    printf("Car %d started washing. length of  Queue : %d\n", id, waiting);
    pthread_mutex_unlock(&mutex);

    // Washing for 3 seconds
    sleep(3);

    printf("Car %d finished washing.\n", id);

    // Free the washing station
    sem_post(&wash_sem);

    return NULL;
}

int main() {
    pthread_t cars[CARS];
    int ids[CARS];

    // Initialize semaphore with 2 stations
    sem_init(&wash_sem, 0, STATIONS);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create car threads
    for (int i = 0; i < CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &ids[i]);
    }

    // Wait for all cars
    for (int i = 0; i < CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    // Cleanup
    sem_destroy(&wash_sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
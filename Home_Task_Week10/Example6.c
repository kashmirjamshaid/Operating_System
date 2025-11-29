#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_ON_BRIDGE 3
#define TOTAL_CARS 10

sem_t bridge_sem;           // Controls number of cars on bridge
pthread_mutex_t print_mutex; // For clean printing

void* car(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&print_mutex);
    printf("Car %d is waiting to enter the bridge...\n", id);
    pthread_mutex_unlock(&print_mutex);

    // Wait for permission to enter bridge
    sem_wait(&bridge_sem);

    pthread_mutex_lock(&print_mutex);
    printf("Car %d STARTED crossing the bridge.\n", id);
    pthread_mutex_unlock(&print_mutex);

    // Random crossing time (1–4 seconds)
    int t = (rand() % 4) + 1;
    sleep(t);

    pthread_mutex_lock(&print_mutex);
    printf("Car %d FINISHED crossing in %d seconds.\n", id, t);
    pthread_mutex_unlock(&print_mutex);

    // Free space on the bridge
    sem_post(&bridge_sem);

    return NULL;
}

int main() {
    pthread_t cars[TOTAL_CARS];
    int ids[TOTAL_CARS];

    srand(time(NULL));

    // Semaphore allows 3 cars at a time
    sem_init(&bridge_sem, 0, MAX_ON_BRIDGE);

    // Initialize mutex
    pthread_mutex_init(&print_mutex, NULL);

    // Create car threads
    for (int i = 0; i < TOTAL_CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &ids[i]);
    }

    // Wait for all cars
    for (int i = 0; i < TOTAL_CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    // Cleanup
    sem_destroy(&bridge_sem);
    pthread_mutex_destroy(&print_mutex);

    return 0;
}
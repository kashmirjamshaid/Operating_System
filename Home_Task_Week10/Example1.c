#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t rooms;              // Counting semaphore for available rooms
pthread_mutex_t mutex;    // protect the occupied counter

int occupied = 0;         // no of occupied rooms

void* person(void* arg) {
    int id = *(int*)arg;

    printf("Person %d is trying to enter...\n", id);

    // Wait for an available room (decrement semaphore)
    sem_wait(&rooms);

    // Lock the counter update
    pthread_mutex_lock(&mutex);
    occupied++;
    printf("Person %d entered. Rooms occupied: %d\n", id, occupied);
    pthread_mutex_unlock(&mutex);

    // Stay for random 1–3 seconds
    int stay = (rand() % 3) + 1;
    sleep(stay);

    // Leaving the room
    pthread_mutex_lock(&mutex);
    occupied--;
    printf("Person %d left. Rooms occupied: %d\n", id, occupied);
    pthread_mutex_unlock(&mutex);

    // Free the room (increment semaphore)
    sem_post(&rooms);

    return NULL;
}

int main() {
    int N = 3;            // Number of rooms
    int totalPeople = 10; // Total threads
    pthread_t people[totalPeople];
    int ids[totalPeople];

    srand(time(NULL)); // For random stay time

    // Initialize semaphore with N rooms
    sem_init(&rooms, 0, N);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads (people)
    for(int i = 0; i < totalPeople; i++) {
        ids[i] = i + 1;
        pthread_create(&people[i], NULL, person, &ids[i]);
    }

    // Wait for all people to complete
    for(int i = 0; i < totalPeople; i++) {
        pthread_join(people[i], NULL);
    }

    // Cleanup
    sem_destroy(&rooms);
    pthread_mutex_destroy(&mutex);

    return 0;
}
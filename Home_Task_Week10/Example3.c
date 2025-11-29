#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define K 4      // Number of computers in the lab
#define STUDENTS 10

sem_t lab_sem;               // Semaphore for available computers
pthread_mutex_t mutex;       // Protects shared array

int computers[K];            // -1 = free, else student ID

void* student(void* arg) {
    int id = *(int*)arg;


    // Wait for a free computer
    sem_wait(&lab_sem);

    // Find and assign the free computer
    pthread_mutex_lock(&mutex);

    int assigned_computer = -1;
    for (int i = 0; i < K; i++) {
        if (computers[i] == -1) {
            computers[i] = id;
            assigned_computer = i;
            break;
        }
    }

    printf("Student %d started using computer %d.\n", id, assigned_computer);

    pthread_mutex_unlock(&mutex);

    // Use computer for random 1–3 seconds
    int use_time = (rand() % 3) + 1;
    sleep(use_time);

    // Student leaves the computer
    pthread_mutex_lock(&mutex);

    computers[assigned_computer] = -1;
    printf("Student %d left computer %d.\n", id, assigned_computer);

    pthread_mutex_unlock(&mutex);

    // Free a computer
    sem_post(&lab_sem);

    return NULL;
}

int main() {
    pthread_t threads[STUDENTS];
    int ids[STUDENTS];

    srand(time(NULL));

    // Initialize computers array to -1 (all free)
    for (int i = 0; i < K; i++) {
        computers[i] = -1;
    }

    // Initialize semaphore
    sem_init(&lab_sem, 0, K);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create student threads
    for (int i = 0; i < STUDENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, student, &ids[i]);
    }

    // Join all students
    for (int i = 0; i < STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup
    sem_destroy(&lab_sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
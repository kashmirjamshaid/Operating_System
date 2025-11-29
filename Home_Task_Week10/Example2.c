#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t download_slots;   // Semaphore to allow max 3 downloads at a time

void* download_file(void* arg) {
    int id = *(int*)arg;


    // Wait for an available download slot
    sem_wait(&download_slots);

    // Start download
    printf("Download %d started.\n", id);

    int time_needed = (rand() % 5) + 1;  // Random 1–5 seconds
    sleep(time_needed);

    // End download
    printf("Download %d finished.\n", id);

    // Free the slot
    sem_post(&download_slots);

    return NULL;
}

int main() {
    pthread_t downloads[8];
    int ids[8];

    srand(time(NULL));

    // Initialize semaphore with 3 download slots
    sem_init(&download_slots, 0, 3);

    // Create 8 download threads
    for(int i = 0; i < 8; i++) {
        ids[i] = i + 1;
        pthread_create(&downloads[i], NULL, download_file, &ids[i]);
    }

    // Wait for all downloads to complete
    for(int i = 0; i < 8; i++) {
        pthread_join(downloads[i], NULL);
    }

    // Clean up
    sem_destroy(&download_slots);

    return 0;
}
// Kashmir Jamshaid
// 23-NTU-CS-1167
// TASK-5
// Create a program that simulates a simple student database system.
// Define a struct: typedef struct { int student_id; char name[50]; float gpa; } Student;
// Create 3 threads, each receiving a different Student struct.
// Each thread prints student info and checks Dean’s List eligibility (GPA ≥ 3.5).
// The main thread counts how many students made the Dean’s List.

#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Define Student structure
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

int dean_count = 0;
pthread_mutex_t lock; // Mutex for safe counter update find lock 

// Thread function
void* check_deans_list(void* arg) {
    Student* s = (Student*)arg;

    printf("Student ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    // Check eligibility for Dean’s List 
    if (s->gpa >= 3.5) {
        printf("Status: Eligible for Dean's List\n\n");
        pthread_mutex_lock(&lock);
        dean_count++;
        pthread_mutex_unlock(&lock);
    } else {
        printf("Status: Not eligible for Dean's List\n\n");
    }

    return NULL;
}

int main() {
    pthread_t threads[3];
    Student students[3] = {
        {101, "Kashmir khan", 3.6},
        {102, " Haider Ali ", 3.7},
        {103, " yehya Khan", 3.8}
    };

    pthread_mutex_init(&lock, NULL);

    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, check_deans_list, &students[i]);
    }

    // Wait for all threads to finish or complete the task 
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: Total students on Dean's List = %d\n", dean_count);

    pthread_mutex_destroy(&lock);
    return 0;
}

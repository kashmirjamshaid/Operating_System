// Kashmir Jamshaid
// 23-NTU-CS-1167
// TASK-3
// Write a program that:
// • Takes an integer input from the user.
// • Creates a thread and passes this integer to it.
// • The thread prints the number, its square, and cube.
// • The main thread waits until completion and prints “Main thread: Work completed.”

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* calculate(void* arg) {
    int num = *(int*)arg;
    printf("Thread: Number = %d\n", num);
    printf("Thread: Square = %d\n", num * num);
    printf("Thread: Cube = %d\n", num * num * num);
    return NULL;
}

int main() {
    pthread_t thread_id;
    int number;

    printf("Enter an integer: ");
    scanf("%d", &number);

    pthread_create(&thread_id, NULL, calculate, &number);
    pthread_join(thread_id, NULL);

    printf("Main thread: Work completed.\n");
    return 0;
}

// Kashmir
// 23-NTU-CS-1167
// TASK-2
// Write a C program that:
// • Creates a thread that prints a personalized greeting message.
// • The message includes the user’s name passed as an argument to the thread.
// • The main thread prints “Main thread: Waiting for greeting…” before joining the created thread.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* greet(void* arg) {
    char* name = (char*)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    char* userName = "Kashmir Jamshaid";

    printf("Main thread: Waiting for greeting...\n");
    pthread_create(&thread, NULL, greet, (void*)userName);
    pthread_join(thread, NULL);
    printf("Main thread: Greeting completed.\n");

    return 0;
}

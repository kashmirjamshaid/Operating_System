// Kashmir Jamshaid
// 23-NTU-CS-1167
// TASK-4
// Write a program that creates a thread to compute the factorial of a number entered by the user.
// • The thread should return the result using a pointer.
// • The main thread prints the result after joining.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* factorial(void* arg) {
    int n = *(int*)arg;
    long long* result = malloc(sizeof(long long));  // Allocate (give ) memory to store result
    *result = 1;

    for (int i = 1; i <= n; i++) {
        *result *= i;
    }

    return result;  // Return the pointer to main thread
}

int main() {
    pthread_t thread_id;
    int number;
    long long* fact_result;

    printf("Enter a number: ");
    scanf("%d", &number);

    pthread_create(&thread_id, NULL, factorial, &number);
    pthread_join(thread_id, (void**)&fact_result);

    printf("Factorial of %d = %lld\n", number, *fact_result);
    printf("Main thread: Work completed.\n");

    free(fact_result);  // Free allocated memory
    return 0;
}


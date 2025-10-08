#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process runs "top"
        execlp("top", "top", NULL);
        perror("execlp failed"); // Only runs if exec fails
    } 
    else if (pid > 0) {
        // Parent waits for child
        printf("Parent PID: %d, waiting for child...\n", getpid());
        wait(NULL);
        printf("Child process finished.\n");
    } 
    else {
        perror("fork failed");
    }

    return 0;
}

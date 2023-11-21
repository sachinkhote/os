#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid > 0) {
        printf("\nI am parent process");
        printf("\nPID=%d", getpid());
        printf("\nChild ID is: %d \n", pid);
    } else if (pid == 0) {
        sleep(2);
        printf("\nI am child process:");
        printf("\nPID=%d", getpid());
        printf("\nParent ID is: %d", getppid());
    } else {
        printf("Failed to fork");
        return 1;
    }
    return 0;
}
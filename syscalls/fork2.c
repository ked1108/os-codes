#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        // Child process
        printf("Child process: PID=%d\n", getpid());
        sleep(10); // Delay to observe the orphan process
    } else if (pid > 0) {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);
    } else {
        // Fork failed
        printf("Fork failed.\n");
    }
    return 0;
}

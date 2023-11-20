#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
        pid = fork();
        
        if (pid == 0) {
            printf("Child process: PID=%d\n", getpid());
        }
    
        else if (pid > 0) {
            printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);
                sleep(10);
                int status;
                wait(&status);
        } 
    
        else {
            printf("Fork failed.\n");
        }
    return 0;
}

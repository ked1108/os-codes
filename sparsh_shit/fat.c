#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t proc2, proc3;
    printf("PID OF P1:%d\n", getpid());

    proc2 = fork();
    if(proc2 == 0) {
        sleep(10);
    } else {
        wait(NULL);
    }
}
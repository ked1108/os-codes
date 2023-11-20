#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t add_pid, sub_pid, div_pid;

    add_pid = fork();
    if(add_pid == 0){
        execl("./addition", NULL);
        perror("Didn't work out");
        exit(1);
    } 
    else if (add_pid == -1) {
        printf("Fork Failed!");
        exit(1);
    }
    else{
        wait(NULL);
        sub_pid = fork();
        if(sub_pid == 0){
            execl("./subtraction", NULL);
            perror("Didn't work out");
            exit(1);
        }
        else if(sub_pid == -1){
            printf("Fork Failed");
            exit(1);
        }
        else{
            wait(NULL);
            div_pid = fork();

            if(div_pid == 0){
                execl("./division", NULL);
                perror("Didn't work out");
                exit(1);
            }
            else if (div_pid == -1) {
                printf("Fork failed");
                exit(1);
            }
            else {
                wait(NULL);
                printf("\nDone!\n");
            }
        }
    }

    return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t ls;
    char* args[] = {"ls", "-l", NULL};
    
    ls = fork();
    if(ls == 0){
        execvp("ls", args);
        perror("Error:\t");
        exit(1);
    }
    else if(ls == -1){
        printf("Fork Failed");
        exit(1);
    }
    else{
        wait(NULL);
    }

    return EXIT_SUCCESS;
}

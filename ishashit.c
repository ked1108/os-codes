#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t child1, child2, child3, child4;
    
    child1 = fork();
    if(child1 == 0){
        int waitPID = 0;
        int status;
        child2 = fork();
        while(waitPID == 0){
            waitPID = waitpid(child2, &status, WNOHANG);
        }
        // Execute
        printf("Done Executing\n");
        exit(1);
    }
    else if(child2 == 0 && child1 != 0){
        int waitPID2 = 0;
        int status2;
        child3 = fork();
        printf("Second Executing\n");
        while(waitPID2 == 0)
            waitPID2 = waitpid(child3, &status2, WNOHANG);

        printf("Done Executing\n");
        exit(1);
    }

    else if(child3 == 0 && child2 != 0){
        int waitPID3 = 0;
        int status3;
        child4 = fork();
        printf("Third Executing\n");
        while(waitPID3 == 0)
            waitPID3 = waitpid(child4, &status3, WNOHANG);

        printf("Done Executing\n");
        exit(1);
    }
    else if(child4 == 0 && child3 != 0){
        printf("Done Executing\n");
        exit(1);
    }
}

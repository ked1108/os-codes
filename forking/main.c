#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t ascii_sum, to_upper;

    char* input = (char*)calloc(100, sizeof(char));
    fgets(input, 100, stdin);

    to_upper = fork();

    if(to_upper == 0){
        execl("./caseconverter", "caseconverter", input, NULL);
        perror("Error!:");
        exit(1);
    }
    else if(to_upper == -1){
        printf("Fork Failed");
        exit(1);
    }
    else{
        wait(NULL);
        ascii_sum = fork();
        
        if(ascii_sum == 0){
            execl("./asciisum", "asciisum", input, NULL);
        }
        else if (ascii_sum == -1) {
            printf("Fork Failed!");
            exit(1);
        }
        else {
            wait(NULL);
            printf("\nParent Process:\t%d", getpid());
        }
    }
    return 0;
}

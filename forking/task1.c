#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    char *input = (char*)calloc(100, sizeof(char));
    fgets(input, 100, stdin);

    pid_t charcount;
    charcount = fork();

    if(charcount == 0){
        unsigned long length = strlen(input);
        printf("Character Count:\t%ld\n", length);
        printf("Process:\t%d\n", getpid());
    }
    else if(charcount == -1){
        printf("Fork failed");
        exit(1);
    }
    else{
        wait(NULL);
        printf("Lower Case:\n");
        for(int i = 0; i < strlen(input)-1; i++){
            printf("%c", tolower(input[i]));
        }
        printf("\nProcess:\t%d\n", getpid());
    }

    return 0;
}

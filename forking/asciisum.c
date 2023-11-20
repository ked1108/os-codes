#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char* string = argv[1];
    int sum = 0;

    for (int i = 0; i < strlen(string); i++) {
        sum+=string[i];
    }

    printf("%d\n", sum);
    printf("Process:\t%d\n", getpid());
    return EXIT_SUCCESS;
}

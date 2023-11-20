#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char* input = argv[1];
    for (int i = 0; i < strlen(input); i++) {
        printf("%c", toupper(input[i]));
    }
    printf("Process:%d\n", getpid());
    return EXIT_SUCCESS;
}

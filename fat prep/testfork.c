#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a = 0;
    fork();
    printf("%d\t", a++);
    fork();
    printf(",%d\t", a++);
    fork();
    printf(",%d\n", a++);


    return EXIT_SUCCESS;
}

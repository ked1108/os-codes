#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *highest(void* arg){
    long a = (long)arg;

    int max=INT_MIN;
    int digit = 0;
    while(a!=0){
        digit = a%10;
        max = (digit>max)?digit:max;
        a /= 10;
    }
    int *result = malloc(sizeof(int));
    *result = max;
    return (void*)result;
}

int main(int argc, char *argv[]){
    pthread_t threadA, threadB;
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    pthread_create(&threadA, NULL, highest, (void*)(long)a);
    pthread_create(&threadB, NULL, highest, (void*)(long)b);

    int *outA, *outB;
    pthread_join(threadA, (void**)&outA);
    pthread_join(threadB, (void**)&outB);

    int output = *outA + *outB;

    printf("output = %d\n", output);

    return EXIT_SUCCESS;
}

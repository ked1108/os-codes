#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

bool flag[2];
int turn;

void *p1(void* args){
    do {
        flag[1] = true;
        turn = 0;
        while(turn == 0 && flag[0]);
        printf("Executing P1 in critical section\n");
        sleep(1);
    }while (1);
}

void *p0(void *args){
    do {
        flag[0] = 1;
        turn = 1;
        while(turn == 1 && flag[1]);
        printf("Executing P2 in critical section\n");
        sleep(1);
    }while (1);
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, p0, NULL);
    pthread_create(&t2, NULL, p1, NULL);

    sleep(5);

    return 0;
}

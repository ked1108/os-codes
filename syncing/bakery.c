#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define N 5

bool choosing[N];
int number[N];
int procs_id[N];

void init() {
    for (int i = 0; i < N; i++) {
        number[i] = 0;
        procs_id[i] = i;
        choosing[i] = false;
    }
}

int max() {
    int m = 0;
    for(int i = 0; i < N; i++) {
        if(m < number[i]) m = number[i];
    }

    return m;
}

void *pi(void* arg) {
    int *i = arg;
    do {
        choosing[*i] = true;
        number[*i] = max() + 1;
        choosing[*i] = false;
        for(int j = 0; j < N; j++) {
            while(choosing[j]);
            while(number[j] != 0 && number[j] < number[*i] && j < *i);
        }
        printf("Executing P%d\n",*i);
        number[*i] = 0;
    } while (true);
}

int main() {
    init();
    pthread_t procs[N];
    for (int i = 0; i < N; i++) {
        pthread_create(&procs[i], NULL, pi, &procs_id[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(procs[i], NULL);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

int state[4];

sem_t S[N];

int LEFT(int philosopher){
    return (philosopher+1) % N;
}

int RIGHT(int philosopher){
    return (philosopher+4) % N;
}

void* philosopher(void* arg) {
    int i = (long)arg;
    do {
        int picked = 0;
        if(state[RIGHT(i)] != EATING && state[LEFT(i)] != EATING){
            sem_wait(&S[i]);
            sem_wait(&S[LEFT(i)]);
            picked = 1;
        }   

        if(picked){
            state[i] = EATING;
            printf("Philosopher %d is eating...\n", i);

            sem_post(&S[i]);
            sem_post(&S[LEFT(i)]);
            state[i] = THINKING;
            break;
        } 

        state[i] = THINKING;
        printf("Philosopher %d is thinking...\n", i);
        sleep(2);

    } while (1); 

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t phils[N];
    for (int i = 0; i < N; i++) {
        sem_init(&S[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&phils[i], NULL, philosopher, (void*)(long)i);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(phils[i], NULL);
    }
    return 0;
}

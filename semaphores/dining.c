#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t chopsticks[5];
sem_t phil[5];

void *Philosophers(void* arg) {
    int *i = (int*) arg;
    printf("Philisopher %d\n", *i);
    sem_wait(&chopsticks[*i]);
    sem_wait(&chopsticks[(*i+1)%5]);
    printf("Philisopher %d\n", *i);
    sem_post(&chopsticks[*i]);
    sem_post(&chopsticks[(*i +1) % 5]);
    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[5];
    for (int i = 0; i < 5; i++) {
        sem_init(&chopsticks[i], 0, 1);
        sem_init(&phil[i], 0, 0);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&philosophers[i], NULL, Philosophers, &i); 
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

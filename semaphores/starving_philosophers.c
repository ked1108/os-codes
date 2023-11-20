#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t room;
sem_t chopsticks[5];
int hunger_level[] = {2, 4, 2, 3, 5};

void eat(int curr){
    printf("Philosopher %d is eating\n", curr+1);
}

void  * philosopher(void* num) {
    int curr = *(int *)num;
    sem_wait(&room);
    printf("Philosopher %d joined the room with hunger level %d\n", curr+1, hunger_level[curr]);
    if (hunger_level[curr] == 1) return (void*)1;
    if(hunger_level[curr] > hunger_level[(curr+1)%5] && (curr != 0)?hunger_level[curr]>hunger_level[curr-1]:hunger_level[curr] > hunger_level[4]){
        sem_wait(&chopsticks[(curr+1)%5]);
        sem_wait(&chopsticks[curr]);

        eat(curr);

        sleep(2);
        sem_post(&chopsticks[curr]);
        sem_post(&chopsticks[(curr+1)%5]);
        sem_post(&room);
    }
}

int main() {
    int a[5];
    pthread_t philosophers[5];

    sem_init(&room, 0, 4);
    for (int i = 0; i < 5; i++) {
        a[i] = i;
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

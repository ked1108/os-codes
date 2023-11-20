#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 20

sem_t mutex, wlock;
int data = 0, r_count = 0;

void* reader(void* arg) {
    int f = (long)arg;
    sem_wait(&mutex);
    r_count++;
    if(r_count == 1){
        sem_wait(&wlock);
    }
    sem_post(&mutex);

    printf("Data read by the reader %d is %d\n", f, data);
    sleep(1);

    sem_wait(&mutex);
    r_count--;
    if(r_count == 0) {
        sem_post(&wlock);
    }
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int f = (long)arg;
    sem_wait(&wlock);
    data++;
    printf("Data written by writer %d is %d\n", f, data);
    sleep(1);
    sem_post(&wlock);

    return NULL;
}

int main(int argc, char *argv[]) {
    
    int i, b;
    pthread_t rtid[N], wtid[N];

    sem_init(&mutex, 0, 1);
    sem_init(&wlock, 0, 1);

    for (size_t i = 0; i < N; i++) {
        pthread_create(&wtid[i], NULL, reader, (void*)i);
        pthread_create(&rtid[i], NULL, writer, (void*)i);
    }

    for (size_t i = 0; i < N; i++) {
        pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }

    return EXIT_SUCCESS;
}

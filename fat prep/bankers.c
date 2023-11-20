#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t mutex, empty, full;
int data = 0;

void add() {
    data += 10;
}

void* producer(void* arg) {
    while(1) {
        sem_wait(&empty);
        sem_wait(&mutex);
        add();
        sem_post(&mutex);
        sem_post(&full);
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    return EXIT_SUCCESS;
}

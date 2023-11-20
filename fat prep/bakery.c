#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 10

int tickets[THREAD_COUNT];
int choosing[THREAD_COUNT];


int max_ticket() {
    int max_t = 0;
    for(int i = 0; i < THREAD_COUNT; i++) {
        max_t = max_t < tickets[i] ? tickets[i] : max_t;
    }

    return max_t;
}

void lock(int thread) {
    choosing[thread] = 1;
    __sync_synchronize();
    int max_t = max_ticket() + 1;
    choosing[thread] = 0;
    
    for(int other = 0; other < THREAD_COUNT; other++) {
        while (choosing[other]);
        __sync_synchronize();
        while(tickets[other] != 0 && (tickets[other] <= tickets[thread]) && other < thread);
    }
}

void unlock(int thread) {
    __sync_synchronize();
    tickets[thread] = 0;
} 

void use_resource(int thread) {
    printf("Using %d\n", thread);
}

void* thread_body(void* arg) {
    long thread = (long)arg;
    lock(thread);
    use_resource(thread);
    unlock(thread);
    return NULL;
}

int main(int argc, char *argv[]) {
    memset((void*)tickets, 0, sizeof(tickets));
    memset((void*)choosing, 0, sizeof(choosing));
    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, &thread_body, (void*)(long)i);
    }
    
    for(int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    return EXIT_SUCCESS;
}

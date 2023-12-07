#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* sum(void* arg) {
    long n = (long)arg;
    
    long s = 0;
    for(long i = 1; i <= n; i++){
        s += i;
    }
    printf("sum:\t%ld\n",s);

    return NULL;
}

int main() {

    pthread_t th1, th2;
    pthread_create(&th1, NULL, sum, (void*)10);
    pthread_create(&th2, NULL, sum, (void*)100);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}
#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    pid_t procA, procB, procC;
    int n;
    scanf("%d", &n);

    int array[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    procA = fork();
    if(procA == 0){
        int count = 0;
        for(size_t i = 0; i < n; i++){
            if(array[i]%2 == 0) count++;
        }
        procB = fork();
        if(procB == 0) {
            int fact = 1;
            for(size_t i = 1; i <= count; i++){
                fact *= i;
            }
            procC = fork();
            if(procC == 0) {
                for(int i = 2; i < fact; i++) {
                    if(fact%i == 0){
                        printf("Not a prime");
                        return 0;
                    }
                }
                printf("Is a prime");
            }
        }
    }

    return EXIT_SUCCESS;
}

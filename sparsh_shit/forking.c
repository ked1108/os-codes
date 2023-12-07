#include <unistd.h>
#include <stdio.h>

int main() {
    // int n;
    // scanf("%d", &n);
    
    for (int i = 0; i < 3; i++) {
        pid_t id = fork();
        if(id == 0){
            printf("const char *, ...")
        }

    }

    // pid_t proc1;
    // proc1 = fork();
    // if(proc1 == -1) {
    //     perror("error creating child process");
    // }
    // else if (proc1 == 0) {
    //     int fact = 1;
    //     for(int i = 1; i < n; i++){
    //         fact *= i;
    //     }
    //     printf("factorial :\t%d", fact);
    // }
    // else {
    //     int sum = 0;
    //     for (int i = 1; i <= n; i++) {
    //         sum += i;
    //     }
    //     printf("sum :\t%d", sum);
    // }


    return 0;
}
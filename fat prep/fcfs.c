#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Proc {
    int pid;
    int arrival;
    int burst;
    int priority;
    int remaining;
};

void sort(struct Proc procs[], int n) {
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1; j++){
            if(procs[j].arrival > procs[j+1].arrival){
                struct Proc temp = procs[j];
                procs[j] = procs[j+1];
                procs[j+1] = temp;
            }
        }
    }
} 

int select_proc(struct Proc procs[], int n, int time){
    int min = INT_MAX, midx = -1;
    for (size_t i = 0; i < n; i++) {
        if(procs[i].burst != 0 && min > procs[i].burst && procs[i].arrival <= time) {
            min = procs[i].burst;
            midx = i;
        } 
    }

    return midx;
}

void fcfs(struct Proc procs[], int n) {
    int turnaroundTime, waitingTime, pid = 0, clock = 0, unset = 0, done = 0;
    float averageWT, averageTT;

    turnaroundTime =  waitingTime = 0;
    averageTT = averageWT = 0.0;

    while(done != n){

        // ACCOUNT FOR IDLE TIME
        if(clock < procs[pid].arrival) clock = procs[pid].arrival;

        clock += procs[pid].burst;
        printf("%d\t", procs[pid].burst);

        turnaroundTime = clock - procs[pid].arrival;
        waitingTime = turnaroundTime - procs[pid].burst;

        averageTT = (averageTT+turnaroundTime)/2.0;
        averageWT = (averageWT+waitingTime)/2.0;
        printf("%d\t%d\t%d:\t\t\t %d \n", procs[pid].pid, turnaroundTime, waitingTime, clock);
        // printf("%d\t%d\t%d:\t\t\t %d \n", pid, turnaroundTime, waitingTime, clock);
        procs[pid].burst = 0;
        pid++;

        done++;

    }

    printf("Average Waiting Time:\t%0.2f\n", averageWT);
    printf("Average Turnaround Time:\t%0.2f\n", averageTT);
}

void print(struct Proc procs[], int n){
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", procs[i].pid, procs[i].arrival, procs[i].burst);
    }
}

int main(int argc, char *argv[]) {

    // STRUCT PROCS 
    // int pid;
    // int arrival;
    // int burst;
    // int priority;
    // int remaining;

    struct Proc procs[5] = {{1, 0, 4, 0, 0}, {2, 5, 1, 0, 0}, {3,10, 9, 0, 0}, {4, 7, 10, 0, 0}, {5, 20, 7, 0, 0}};

    sort(procs, 5);
    fcfs(procs, 5);

    return EXIT_SUCCESS;
}

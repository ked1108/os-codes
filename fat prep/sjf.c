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

void sjf(struct Proc procs[], int n) {
    int turnaroundTime, waitingTime, pid = 0, clock = 0, unset = 0, done = 0;
    float averageWT, averageTT;

    turnaroundTime =  waitingTime = 0;
    averageTT = averageWT = 0.0;

    while(done != n){
        if(pid == -1){
            pid = select_proc(procs, n, clock);
            if(pid != -1) continue;
            else {
                clock++;
                continue;
            }
        }

        else{
            clock += procs[pid].burst;

            turnaroundTime = clock - procs[pid].arrival;
            waitingTime = turnaroundTime - procs[pid].burst;


            averageTT = (averageTT+turnaroundTime)/2.0;
            averageWT = (averageWT+waitingTime)/2.0;
            printf("%d\t%d\t%d\n", procs[pid].pid, turnaroundTime, waitingTime);
            pid = -1;
            procs[pid].burst = 0;

            done++;
            continue;
        }

        clock++;
    }

    printf("Average Waiting Time:\t%0.2f\n", averageWT);
    printf("Average Turnaround Time:\t%0.2f\n", averageTT);
}

int main(int argc, char *argv[]) {

    struct Proc procs[] = {{1, 0, 4, 0, 0}, {2, 0, 1, 0, 0}, {3, 0, 9, 0, 0}, {4, 0, 10, 0, 0}, {5, 0, 7, 0, 0}};

    sort(procs, 5);
    sjf(procs, 5);

    return EXIT_SUCCESS;
}

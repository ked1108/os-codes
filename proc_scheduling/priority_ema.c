#include <stdio.h>
#include <stdlib.h>

#define A 0.5
#define B 0.8

typedef struct PCB{
    int pid;
    int arrival;
    int burst;
    int priority;
    int completed;
    int start;
    int turnaround;
    int waiting;
} PCB;

void swap(PCB* p1, PCB* p2){
    PCB temp = *p1;
    *p1 = * p2;
    *p2 = temp;
}

void sort(PCB processes[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1-i; j++){
            if(processes[j].arrival > processes[j+1].arrival){
                swap(&processes[j], &processes[j+1]);
            }
        }
    }
}

void priorityEMA(PCB procs[], int n){
    int done = 0;
    int clock = 0;
    PCB* running = (PCB*)malloc(sizeof(PCB));
    running = NULL;
    while(done <= n-1){
        for(int i = 0; i < n; i++){
            if(running == NULL || procs+i != running && procs[i].priority > running->priority && procs[i].arrival <= clock && procs[i].completed < procs[i].burst){
                running = procs+i;
                printf("%d\n", i);
            }
            else if(procs[i].arrival <= clock && procs+i != running && procs[i].completed != procs[i].burst){
                procs[i].priority += A*(clock - procs[i].start);
            }
        }

        if (running->completed < running->burst){
            running->completed++;
            running->priority += B*(clock - running->start);
        }
        else{
            printf("PID:\t%d completed\t%d\n", running->pid, running->completed);
            running->turnaround = running->start - clock - 1;
            running->waiting = running->turnaround - running->burst;
            running = NULL;
            done++;
        }    
        clock++;
    }
}

float averageWaiting(PCB procs[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += procs[i].waiting;
    }
    return (float)sum/n;
}

float averageTurnaround(PCB procs[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += procs[i].turnaround;
    }
    return (float)sum/n;
}

void printProcs(PCB processes[], int n){
    for(int i = 0; i < n; i++){
        printf("PID:\t%d\n", processes[i].pid);
    }
}

int main(){

    PCB procs[] =  {{1, 10, 5, 1, 0, 0},
                    {2, 15, 15, 1, 0, 0},
                    {3, 3, 10, 1, 0, 0}};

    sort(procs, 3);
    printProcs(procs, 3);
    priorityEMA(procs, 3);
    printf("Waiting:\t%0.2f", averageWaiting(procs, 3));
    printf("Turnaround:\t%0.2f", averageTurnaround(procs, 3));

    return 0;
}

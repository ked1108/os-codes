#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int arrival;
    int burst;
} Process; 

void swap(Process* A, Process* B){
    Process temp = *A;
    *A = *B;
    *B = temp;
}

float average(int array[], int n){
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    float avg = ((float)sum)/n;
    return avg;
}

void sort(Process p[], int n){
    for(int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1; j++) {
            if(p[j].arrival > p[j+1].arrival){
                swap(&p[j], &p[j+1]);
            }
        }
    }
}

void fcfs(Process p[], int n){
    int wt[n], tt[n];
    int time = p[0].arrival;
    for (int i = 0; i < n; i++) {
        if(time < p[i].arrival) time+=p[i].arrival-time;
        wt[i] = time;
        tt[i] = time + p[i].burst - p[i].arrival;
        printf("PID:\t%d,\tStart:\t%d,\tEnd:\t%d\n",p[i].pid, time, time+p[i].burst);
        time += p[i].burst;
    }

    printf("Average Turnaround Time:\t\t%0.2f \n", average(tt, n));
    printf("Average Waiting Time:\t\t%0.2f \n", average(wt, n));
}


int main(){
    // Process *p = (Process*)malloc(sizeof(Process)*5);
    Process p[] = {{1, 0, 4}, {2, 4, 2}, {3, 2, 3}, {4, 17, 6}, {5, 6, 2}};
    sort(p, 5);
    fcfs(p, 5);
    return 0;
}

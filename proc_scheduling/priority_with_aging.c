#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int arrival;
    int burst;
    int workdone;
    int priority;
    int turn_around;
    int waiting;
} Process; 

int notIn(Process p, Process ps[], int n){
    for(int i = 0; i < n; i++){
        if(p.pid == ps[i].pid){
            return 0;
        }
    }
    return 1;
}

void sort(Process p[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(p[j].arrival > p[j+1].arrival){
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void priority(Process p[], int n){
    // int clock = 0;
    sort(p, n);
    Process done[n];
    int dp = 0;
    int curr = 0;
    int busy = 0;
    int clock = 0;
    while(dp<n){
        if(busy == 0){
            int max_p = 0;
            for(int i =0; i < n; i++){
                if(max_p <= p[i].priority && p[i].arrival <= clock && notIn(p[i], done, n)){
                    curr = i;
                    max_p = p[i].priority;
                }
            }
            busy = 1;
        }

        for (int i = 0; i < n; i++){
            if(p[i].arrival <= clock && notIn(p[i], done, n) && i != curr){
                p[i].priority++;
            }
        }

        if(p[curr].workdone != p[curr].burst) p[curr].workdone++;
        else{
            p[curr].turn_around = clock - p[curr].arrival;
            p[curr].waiting = p[curr].turn_around - p[curr].burst;
            p[curr].priority = -1;
            done[dp++] = p[curr];
            printf("Finished: %d %d %d\n", p[curr].pid, p[curr].waiting, p[curr].turn_around);
            busy = 0;
        }
        clock++;
    }
}

double avgWT(Process p[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum+=p[i].waiting;
    }
    return (double)sum/n;
}

double avgTT(Process p[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum+=p[i].turn_around;
    }
    return (double)sum/n;
}

int main(){
    Process p[] = {{1, 0, 4, 0, 1}, 
                   {2, 4, 2, 0, 4}, 
                   {3, 2, 3, 0, 5}, 
                   {4, 6, 6, 0, 6}, 
                   {5, 6, 2, 0, 3}};
    priority(p, 5);

    printf("Average Waiting Time:\t%lf\n", avgWT(p, 5));
    printf("Average Turnaround Time:\t%lf\n", avgTT(p, 5));

    return 0;
}

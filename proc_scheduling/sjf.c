#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Process {
    int pid;
    int arrival;
    int burst;
    int workdone;
    int turn_around;
    int waiting;
} Process; 

void swap(Process* A, Process* B){
    Process temp = *A;
    *A = *B;
    *B = temp;
}

int isInQ(Process p[], Process s,int n){
    for (int i = 0; i < n; i++) {
        if(p[i].pid == s.pid){
            return 1;
        }
    }
    return 0;
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

void sjf(Process p[], int n){
    Process done[n];
    int dp = 0;
    int clock = 0;
    int min = -1;
    while(dp < n){
        if(min == -1){
            int m_burst = 9999;
            for (int i = 0; i < n; i++) {
                if(p[i].burst < m_burst && !isInQ(done, p[i], n) && p[i].arrival <= clock){
                    min = i;
                    m_burst = p[i].burst;
                }
            }

        }
        if(p[min].workdone != p[min].burst)
            p[min].workdone++;
        else{
            p[min].turn_around = clock- p[min].arrival;
            p[min].waiting = p[min].turn_around - p[min].burst; 
            done[dp++] = p[min];
            printf("Process finished: %d %d %d\n", p[min].pid, p[min].waiting, p[min].turn_around);
            min = -1;
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

int main() {
    Process p[] = {{1, 0, 4, 0}, 
                   {2, 4, 2, 0}, 
                   {3, 2, 3, 0}, 
                   {4, 6, 6, 0}, 
                   {5, 6, 2, 0}};
    sort(p, 5);
    sjf(p, 5);
    printf("Average Waiting Time:\t%lf\n", avgWT(p, 5));
    printf("Average Turnaround Time:\t%lf\n", avgTT(p, 5));
    return 0;
}

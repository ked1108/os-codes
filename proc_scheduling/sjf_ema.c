#include <stdio.h>

#define ALPHA 0.5

typedef struct Process{
    int pid;
    int arrival;
    int burst;
    int workdone;
    int expected_burst;
    int turn_around;
    int waiting;
} Process;

int notIn(Process p, Process ps[], int n){
    for(int i = 0; i < n; i++){
        if(p.pid == ps[i].pid)   return 0;
    }
    return 1;
}

int expected_averaging(int pid, Process p[]){
    if(pid == 0){
        return p[pid].burst;
    }
    else{
        return ALPHA*p[pid-1].burst + (1-ALPHA)*p[pid-1].expected_burst;
    }
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

void sjf_ema(Process p[], int n){
    for (int i = 0; i < n; i++) {
        p[i].expected_burst = expected_averaging(i, p);
        printf("Expected Burst Time of process %d:%d\n", p[i].pid, p[i].expected_burst);
    }

    printf("\n\n");

    Process done[n];
    int dp = 0;
    int curr = 0;
    int min = -1;
    int clock = 0;


    while(dp<n){
        int m_burst = 9999;
        min=-1;
        for(int i = 0; i < n; i++){
            if(p[i].expected_burst < m_burst && notIn(p[i], done, n) && p[i].arrival <= clock){
                min = i;
                m_burst = p[i].expected_burst;
            }
        }

        if(p[min].workdone != p[min].expected_burst)
            p[min].workdone++;

        else{
            p[min].turn_around = clock- p[min].arrival;
            p[min].waiting = p[min].turn_around - p[min].expected_burst; 
            done[dp++] = p[min];
            printf("Process finished: %d %d %d\n", p[min].pid, p[min].waiting, p[min].turn_around);
        }

        clock++;
    }
}

void sjf(Process p[], int n){
    Process done[n];
    int dp = 0;

    int min = -1;
    int busy = 0;
    int clock = 0;
    while(dp<n){
        int m_burst = 9999;
        min=-1;
        for(int i = 0; i < n; i++){
            if(p[i].burst < m_burst && notIn(p[i], done, n) && p[i].arrival <= clock){
                min = i;
                m_burst = p[i].burst;
            }
        }

        if(p[min].workdone != p[min].burst)
            p[min].workdone++;

        else{
            p[min].turn_around = clock- p[min].arrival;
            p[min].waiting = p[min].turn_around - p[min].burst; 
            done[dp++] = p[min];
            printf("Process finished: %d %d %d\n", p[min].pid, p[min].waiting, p[min].turn_around);
        }
        clock++;
    }
}

double avgWT_EMA(Process p[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum+=p[i].expected_burst;
    }
    return (double)sum/n;
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
    Process p1[] = {{1, 0, 5, 0, 0, 0},
                   {2, 1, 8, 0, 0, 0}, 
                   {3, 2, 4, 0, 0, 0}, 
                   {4, 4, 6, 0, 0, 0}, 
                   {5, 6, 10,0, 0, 0}};

    Process p2[] = {{1, 0, 5, 0, 0, 0},
                   {2, 1, 8, 0, 0, 0}, 
                   {3, 2, 4, 0, 0, 0}, 
                   {4, 4, 6, 0, 0, 0}, 
                   {5, 6, 10,0, 0, 0}};
    sort(p1, 5);
    sort(p2, 5);

    printf("*SHORTEST JOB FIRST*\n");
    sjf(p1, 5);
    printf("Average Waiting Time: %lf\n", avgWT(p1, 5));
    printf("Average Turn around Time: %lf\n\n", avgTT(p1, 5));

    printf("*SHORTEST JOB FIRST WITH EXPECTED MOVING AVERAGE*\n");
    sjf_ema(p2, 5);
    printf("Average Waiting Time: %lf\n", avgWT_EMA(p2, 5));
    printf("Average Turn around Time: %lf\n",avgTT(p2, 5));

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct Process{
    int pid;
    int arrival;
    int burst;
    int workdone;
    int turn_around;
    int waiting;
} Process;

typedef struct Processs{
    int pid;
    int arrival;
    int burst;
    int priority;
    int workdone;
    int turn_around;
    int waiting;
} Processs;

int notIn(Process p, Process ps[], int n){
    for(int i = 0; i < n; i++){
        if(p.pid == ps[i].pid)   return 0;
    }
    return 1;
}

int notInn(Processs p, Processs ps[], int n){
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

void sorts(Processs p[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(p[j].arrival > p[j+1].arrival){
                Processs temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void premp(Process p[], int n){
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

void priority(Processs p[], int n){
    // int clock = 0;
    sorts(p, n);
    Processs done[n];
    int dp = 0;
    int curr = 0;
    int clock = p[curr].arrival;
    while(dp<n){
        for(int i =0; i < n; i++){
            if(p[curr].priority < p[i].priority && p[i].arrival <= clock && notInn(p[i], done, n)){
                curr = i;
            }
        }

        if(p[curr].workdone != p[curr].burst) p[curr].workdone++;
        else{
            p[curr].turn_around = clock - p[curr].arrival;
            p[curr].waiting = p[curr].turn_around - p[curr].burst;
            p[curr].priority = -1;
            done[dp++] = p[curr];
            // printf("PID:%d\n", done[dp-1].pid);
            printf("Finished: %d %d %d\n", p[curr].pid, p[curr].waiting, p[curr].turn_around);
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

double avgWT2(Processs p[], int n){
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

double avgTT2(Processs p[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum+=p[i].turn_around;
    }
    return (double)sum/n;
}

int main(){
    Process p1[] = {{1, 0, 3, 0, -1, 0}, 
                    {2, 5, 2, 0, -1, 0}, 
                    {3, 4, 3, 0, -1, 0}, 
                    {4, 4, 5, 0, -1, 0}, 
                    {5, 6, 7, 0, -1, 0}};

    Processs p2[] = {{1, 0, 3, 1, 0, -1, 0},
                     {2, 5, 2, 3, 0, -1, 0}, 
                     {3, 4, 3, 2, 0, -1, 0}, 
                     {4, 4, 5, 5, 0, -1, 0}, 
                     {5, 6, 7, 1, 0, -1, 0}};
    premp(p1, 5);
    priority(p2, 5);
    
    printf("Average Waiting Time of SJF:\t%0.2lf\n", avgWT(p1, 5));
    printf("Average Waiting Time of Priority:\t%0.2lf\n", avgWT2(p2, 5));

    printf("Average Turn Around Time of SJF:\t%0.2lf\n", avgTT(p1, 5));
    printf("Average Turn Around Time of Priority:\t%0.2lf\n", avgTT2(p2, 5));
    return 0;
}

#include<stdio.h>  

#define QUANT 4

typedef struct Process{
    int pid;
    int arrival;
    int burst;
    int workdone;
    int turn_around;
    int waiting;
} Process;

void sort(Process p[], int n){
    for(int i = 0; i < n-1; i++){
        for (int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j+1].arrival){
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void roundrobin(Process p[], int n){
    Process ready[100];
    int start = 0;
    int rp = 0;
    int base = 1;
    Process done[n];
    int dp = 0;
    int curr = 0;
    int clock = 0;

    while(dp < n){
        if(p[curr].workdone == p[curr].burst){
            p[curr].turn_around = clock - p[curr].arrival;
            p[curr].waiting = p[curr].turn_around - p[curr].burst;
            done[dp++] = p[curr];
            printf("Finished: %d %d %d\n", p[curr].pid, p[curr].waiting, p[curr].turn_around);
            if(base < n){
                curr = base++;
            }
            else{
                curr = start++;
            }
        }

        else if(p[curr].workdone != p[curr].burst && p[curr].workdone != 0 && p[curr].workdone%QUANT == 0){
            ready[rp++] = p[curr];
            if(base < n){
                curr = base++;
            }
            else{
                curr = start++;
            }
        }

        else{
            p[curr].workdone++;
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
    roundrobin(p, 5);
    printf("Average Waiting Time:\t%lf\n", avgWT(p, 5));
    printf("Average Turnaround Time:\t%lf\n", avgTT(p, 5));

}

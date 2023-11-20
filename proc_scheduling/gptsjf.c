#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

void sjf(struct Process processes[], int n) {
    int completion_time[n];
    int waiting_time[n];
    int turnaround_time[n];

    int total_time = 0;
    double total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        completion_time[i] = 0;
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completed = 0;
    int current_time = 0;
    int min_burst_time_index;

    while (completed < n) {
        min_burst_time_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && completion_time[i] == 0) {
                if (min_burst_time_index == -1 || processes[i].burst_time < processes[min_burst_time_index].burst_time) {
                    min_burst_time_index = i;
                }
            }
        }

        if (min_burst_time_index != -1) {
            completion_time[min_burst_time_index] = current_time + processes[min_burst_time_index].burst_time;
            waiting_time[min_burst_time_index] = current_time - processes[min_burst_time_index].arrival_time;
            turnaround_time[min_burst_time_index] = waiting_time[min_burst_time_index] + processes[min_burst_time_index].burst_time;
            
            total_waiting_time += waiting_time[min_burst_time_index];
            total_turnaround_time += turnaround_time[min_burst_time_index];
            
            current_time = completion_time[min_burst_time_index];
            completed++;
        } else {
            current_time++;
        }
    }

    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    sjf(processes, n);

    return 0;
}

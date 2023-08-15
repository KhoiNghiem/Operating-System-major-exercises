#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct process {
    int process_id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

int quantum;
int n;

void sort_processes_by_burst_time(struct process *processes) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                struct process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void calculate_waiting_time(struct process *processes) {
    int i, total_time = 0;
    for (i = 0; i < n; i++) {
        total_time += processes[i].burst_time;
        processes[i].waiting_time = total_time - processes[i].burst_time;
    }
}

void calculate_turnaround_time(struct process *processes) {
    int i;
    for (i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

void RR_SJF(struct process *processes) {
    int i, j, k;
    int time = 0;
    int complete = 0;
    int shortest = 0;
    int finished[MAX];
    for (i = 0; i < n; i++) {
        finished[i] = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }
    while (complete != n) {
        shortest = -1;
        for (j = 0; j < n; j++) {
            if ((processes[j].remaining_time > 0) && (finished[j] == 0)) {
                if (shortest == -1) {
                    shortest = j;
                } else if (processes[j].remaining_time < processes[shortest].remaining_time) {
                    shortest = j;
                }
            }
        }
        if (shortest == -1) {
            continue;
        }
        for (k = 0; k < quantum; k++) {
            if (processes[shortest].remaining_time > 0) {
                processes[shortest].remaining_time--;
                time++;
                if (processes[shortest].remaining_time == 0) {
                    complete++;
                    finished[shortest] = 1;
                    break;
                }
            }
        }
    }
}

int main() {
    int i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the quantum: ");
    scanf("%d", &quantum);
    struct process processes[n];
    for (i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    sort_processes_by_burst_time(processes);
    RR_SJF(processes);
    calculate_waiting_time(processes);
    calculate_turnaround_time(processes);

    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    return 0;
}

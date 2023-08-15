#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int burst_time;
    int priority;
} Process;

Process processes[MAX_PROCESSES];
int num_processes = 0;

void input_processes() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    int i;
    for (i = 0; i < num_processes; i++) {
        printf("Enter process ID, burst time, and priority (separated by a space): ");
        scanf("%d%d%d", &processes[i].process_id, &processes[i].burst_time, &processes[i].priority);
    }
}

void add_new_process() {
    int new_process_id, new_burst_time, new_priority;
    printf("Enter the new process ID, burst time, and priority (separated by a space): ");
    scanf("%d%d%d", &new_process_id, &new_burst_time, &new_priority);

    Process new_process;
    new_process.process_id = new_process_id;
    new_process.burst_time = new_burst_time;
    new_process.priority = new_priority;

    int i, j;
    int insert_location = -1;
    for (i = 0; i < num_processes; i++) {
        if (new_process.priority < processes[i].priority) {
            insert_location = i;
            break;
        }
    }

    if (insert_location == -1) {
        processes[num_processes++] = new_process;
    } else {
        for (j = num_processes - 1; j >= insert_location; j--) {
            processes[j + 1] = processes[j];
        }
        processes[insert_location] = new_process;
        num_processes++;
    }
}


int find_next_process() {
    int i, selected_process = 0;
    for (i = 1; i < num_processes; i++) {
        if (processes[i].burst_time > 0 && (processes[i].priority > processes[selected_process].priority || processes[selected_process].burst_time <= 0)) {
            selected_process = i;
        }
    }
    return selected_process;
}


int main() {
    input_processes();

    int current_time = 0;
    int selected_process = find_next_process();
    while (selected_process >= 0) {
        printf("Executing process %d from time %d to %d\n", processes[selected_process].process_id, current_time, current_time + processes[selected_process].burst_time);
        current_time += processes[selected_process].burst_time;
        processes[selected_process].burst_time = 0;

        int all_processes_completed = 1;
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].burst_time > 0) {
                all_processes_completed = 0;
                break;
            }
        }

        if (all_processes_completed) {
            break;
        }

        printf("Do you want to add a new process? (y/n): ");
        char answer[10];
        scanf("%s", answer);
        if (answer[0] == 'y') {
            add_new_process();
        }

        selected_process = find_next_process();
    }

    return 0;
}




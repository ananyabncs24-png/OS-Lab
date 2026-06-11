#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int queue_type; // 1 = System Process, 2 = User Process
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
};

// Function to sort processes by arrival time initially
void sortByArrivalTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nFor Process P%d:\n", p[i].id);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst_time);
        printf("Enter Queue Type (1 for System Process, 2 for User Process): ");
        scanf("%d", &p[i].queue_type);
        p[i].is_completed = false;
    }

    // Sort by arrival time to properly mimic timeline
    sortByArrivalTime(p, n);

    int current_time = 0;
    int completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\nGantt Chart Execution Sequence:\n");

    while (completed < n) {
        int chosen_index = -1;

        // 1. Check for ready System Processes (Queue 1) first
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed && p[i].queue_type == 1) {
                chosen_index = i;
                break; // Since sorted by arrival time, this is the FCFS choice
            }
        }

        // 2. If no system processes are ready, look for ready User Processes (Queue 2)
        if (chosen_index == -1) {
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && !p[i].is_completed && p[i].queue_type == 2) {
                    chosen_index = i;
                    break; // Since sorted by arrival time, this is the FCFS choice
                }
            }
        }

        // 3. CPU Idle State Handler
        if (chosen_index == -1) {
            // Find the minimum arrival time among uncompleted processes to jump to
            int min_arrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!p[i].is_completed && p[i].arrival_time < min_arrival) {
                    min_arrival = p[i].arrival_time;
                }
            }
            printf("| IDLE (%d to %d) ", current_time, min_arrival);
            current_time = min_arrival;
            continue;
        }

        // 4. Process execution (FCFS processing means complete execution)
        printf("| P%d (%d to ", p[chosen_index].id, current_time);
        
        current_time += p[chosen_index].burst_time;
        p[chosen_index].completion_time = current_time;
        p[chosen_index].is_completed = true;
        completed++;

        printf("%d) ", current_time);

        // Calculate Turnaround and Waiting metrics
        p[chosen_index].turnaround_time = p[chosen_index].completion_time - p[chosen_index].arrival_time;
        p[chosen_index].waiting_time = p[chosen_index].turnaround_time - p[chosen_index].burst_time;

        total_tat += p[chosen_index].turnaround_time;
        total_wt += p[chosen_index].waiting_time;
    }
    printf("|\n");

    // Print Results Table
    printf("\n========================================================================\n");
    printf("Process\tType\t\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    printf("========================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%s\t%d\t%d\t%d\t%d\t\t%d\n", 
               p[i].id, 
               (p[i].queue_type == 1) ? "System" : "User  ", 
               p[i].arrival_time, 
               p[i].burst_time, 
               p[i].waiting_time, 
               p[i].turnaround_time,
               p[i].completion_time);
    }
    printf("========================================================================\n");

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}

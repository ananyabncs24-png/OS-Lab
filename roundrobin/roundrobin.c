#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
};

int main() {
    int n, time_quantum;
    int current_time = 0;
    int completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int queue[100]; // Ready queue
    int front = 0, rear = 0;
    bool in_queue[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].is_completed = false;
        in_queue[i] = false;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    // Sort processes by arrival time initially
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Push the first process into the ready queue
    queue[rear++] = 0;
    in_queue[0] = true;

    while (completed < n) {
        // If queue is empty, advance time to the next arriving process
        if (front == rear) {
            int next_arrival = -1;
            for (int i = 0; i < n; i++) {
                if (!p[i].is_completed) {
                    if (next_arrival == -1 || p[i].arrival_time < next_arrival) {
                        next_arrival = p[i].arrival_time;
                    }
                }
            }
            current_time = next_arrival;
            
            // Push newly arrived processes into the queue
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && !p[i].is_completed && !in_queue[i]) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
        }

        int idx = queue[front++]; // Pop process from queue
        
        // Execute process for time quantum or remaining time, whichever is smaller
        if (p[idx].remaining_time > time_quantum) {
            current_time += time_quantum;
            p[idx].remaining_time -= time_quantum;
        } else {
            current_time += p[idx].remaining_time;
            p[idx].remaining_time = 0;
            p[idx].is_completed = true;
            completed++;

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_tat += p[idx].turnaround_time;
            total_wt += p[idx].waiting_time;
        }

        // Check and add new processes that arrived while the current process was executing
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed && !in_queue[i]) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }

        // If the current process is not finished, put it back at the end of the queue
        if (!p[idx].is_completed) {
            queue[rear++] = idx;
        }
    }

    // Print Results
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}

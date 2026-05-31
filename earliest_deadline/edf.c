#include <stdio.h>
#include <stdbool.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time;
    int period;
    int remaining_time;
    int current_deadline; // Dynamic absolute deadline (e.g., 5, 10, 15...)
} Task;

// Helper function to find Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Helper function to find Least Common Multiple (LCM) for Hyperperiod
int find_hyperperiod(Task tasks[], int n) {
    int lcm = tasks[0].period;
    for (int i = 1; i < n; i++) {
        lcm = (lcm * tasks[i].period) / gcd(lcm, tasks[i].period);
    }
    return lcm;
}

// Step 1: Check Schedulability for EDF
bool check_schedulability(Task tasks[], int n) {
    double utilization = 0.0;
    for (int i = 0; i < n; i++) {
        utilization += (double)tasks[i].execution_time / tasks[i].period;
    }

    printf("\n--- Schedulability Check ---\n");
    printf("Total CPU Utilization (U): %.4f\n", utilization);

    // EDF bound is always 1.0 (100% CPU utilization)
    if (utilization <= 1.0) {
        printf("Result: Schedulable (EDF guarantees 100%% utilization efficiency).\n");
        return true;
    } else {
        printf("Result: NOT Schedulable (Utilization %.2f%% exceeds 100%% CPU capacity).\n", utilization * 100);
        return false;
    }
}

// Step 2: Simulate EDF Execution and print Gantt Chart
void simulate_edf(Task tasks[], int n, int hyperperiod) {
    printf("\n--- Gantt Chart / Execution Order (0 to %d ms) ---\n", hyperperiod);
    printf("Time\tExecuting Task\t[Current Absolute Deadlines]\n");
    printf("----------------------------------------------------------\n");

    // Initialize tracking variables
    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = 0;
        tasks[i].current_deadline = 0;
    }

    for (int t = 0; t < hyperperiod; t++) {
        // 1. Handle new task arrivals
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                // Check if the previous instance failed to finish before this arrival (deadline miss)
                if (tasks[i].remaining_time > 0) {
                    printf("[Time %d] ALERT: Task %d missed its deadline!\n", t, tasks[i].id);
                }
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].current_deadline = t + tasks[i].period; // Absolute deadline updates dynamically
            }
        }

        // 2. Find the ready task with the EARLIEST absolute deadline
        int active_task_idx = -1;
        int earliest_deadline = 999999; // Sentinel value representing infinity

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (tasks[i].current_deadline < earliest_deadline) {
                    earliest_deadline = tasks[i].current_deadline;
                    active_task_idx = i;
                }
            }
        }

        // 3. Execute the chosen task for 1 time unit
        if (active_task_idx != -1) {
            printf("%d-%d\tTask %d\t\t", t, t + 1, tasks[active_task_idx].id);
            
            // Debug text to show what deadlines look like at this moment
            printf("[");
            for(int i=0; i<n; i++) {
                if (tasks[i].remaining_time > 0) printf("T%d DL:%d ", tasks[i].id, tasks[i].current_deadline);
            }
            printf("]\n");

            tasks[active_task_idx].remaining_time--;
        } else {
            printf("%d-%d\tIDLE\n", t, t + 1);
        }
    }
}

int main() {
    int n;
    Task tasks[MAX_TASKS];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter Execution Time and Period for Task %d: ", tasks[i].id);
        scanf("%d %d", &tasks[i].execution_time, &tasks[i].period);
    }

    // Check schedulability and simulate
    if (check_schedulability(tasks, n)) {
        int hyperperiod = find_hyperperiod(tasks, n);
        simulate_edf(tasks, n, hyperperiod);
    }

    return 0;
}

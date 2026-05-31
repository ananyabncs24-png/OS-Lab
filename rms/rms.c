#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time;
    int period;
    int remaining_time;
    int next_deadline;
} Task;

// Helper function to find Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Helper function to find Least Common Multiple (LCM) to calculate Hyperperiod
int find_hyperperiod(Task tasks[], int n) {
    int lcm = tasks[0].period;
    for (int i = 1; i < n; i++) {
        lcm = (lcm * tasks[i].period) / gcd(lcm, tasks[i].period);
    }
    return lcm;
}

// Sort tasks by period ascending (Lower period = Higher priority)
void sort_by_priority(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

// Step 1 & 2: Check Schedulability using Liu & Layland Bound
bool check_schedulability(Task tasks[], int n) {
    double utilization = 0.0;
    for (int i = 0; i < n; i++) {
        utilization += (double)tasks[i].execution_time / tasks[i].period;
    }

    // Liu & Layland bound formula: n * (2^(1/n) - 1)
    double bound = n * (pow(2.0, 1.0 / n) - 1.0);

    printf("\n--- Schedulability Check ---\n");
    printf("Total CPU Utilization (U): %.4f\n", utilization);
    printf("RMS Schedulability Bound: %.4f\n", bound);

    if (utilization <= bound) {
        printf("Result: Schedulable (Guaranteed to meet all deadlines).\n");
        return true;
    } else if (utilization <= 1.0) {
        printf("Result: Maybe Schedulable (Exceeds RM bound but <= 100%% utilization. Simulating anyway...)\n");
        return true;
    } else {
        printf("Result: NOT Schedulable (Utilization %.2f%% exceeds 100%% CPU capacity).\n", utilization * 100);
        return false;
    }
}

// Step 3: Simulate Execution and print Gantt Chart
void simulate_rms(Task tasks[], int n, int hyperperiod) {
    printf("\n--- Gantt Chart / Execution Order (0 to %d ms) ---\n", hyperperiod);
    printf("Time\tExecuting Task\n");
    printf("-------------------------\n");

    // Initialize tracking variables
    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = 0; 
        tasks[i].next_deadline = 0;
    }

    for (int t = 0; t < hyperperiod; t++) {
        // 1. Arrive new jobs at their periods
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                // If a task hasn't finished its previous instance, we have a deadline miss
                if (tasks[i].remaining_time > 0) {
                    printf("[Time %d] ALERT: Task %d missed its deadline!\n", t, tasks[i].id);
                }
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = t + tasks[i].period;
            }
        }

        // 2. Find highest priority task that is ready to run
        int active_task_idx = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                active_task_idx = i; // First one found is highest priority because array is sorted
                break;
            }
        }

        // 3. Execute the task for 1 time unit
        if (active_task_idx != -1) {
            printf("%d-%d\tTask %d\n", t, t + 1, tasks[active_task_idx].id);
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

    // Sort tasks by period (lowest period = index 0 = highest priority)
    sort_by_priority(tasks, n);

    // Check if the system is schedulable
    if (check_schedulability(tasks, n)) {
        int hyperperiod = find_hyperperiod(tasks, n);
        simulate_rms(tasks, n, hyperperiod);
    }

    return 0;
}

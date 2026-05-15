#include <stdio.h>

// Function to find GCD for LCM calculation
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b; b = a % b; a = temp;
    }
    return a;
}

// Function to find LCM of an array of numbers (The Hyperperiod)
int find_hyperperiod(int periods[], int n) {
    int res = periods[0];
    for (int i = 1; i < n; i++)
        res = (res * periods[i]) / gcd(res, periods[i]);
    return res;
}

typedef struct {
    int id;
    int capacity;
    int period;
    int deadline;
    int remaining;
} Task;

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    int periods[n];

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d Capacity: ", i + 1);
        scanf("%d", &tasks[i].capacity);
        printf("Task %d Period: ", i + 1);
        scanf("%d", &tasks[i].period);

        tasks[i].remaining = tasks[i].capacity;
        tasks[i].deadline = tasks[i].period;
        periods[i] = tasks[i].period;
    }

    int hyperperiod = find_hyperperiod(periods, n);
    printf("\n--- Calculated Hyperperiod: %d units ---\n", hyperperiod);

    for (int t = 0; t < hyperperiod; t++) {
        int selected = -1;
        int min_deadline = 1e9; // Very large number

        // 1. Check for Task Arrival/Reset at each period boundary
        for (int i = 0; i < n; i++) {
            if (t > 0 && t % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].capacity;
                tasks[i].deadline = t + tasks[i].period;
            }
        }

        // 2. EDF Logic: Pick task with the nearest deadline
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                if (tasks[i].deadline < min_deadline) {
                    min_deadline = tasks[i].deadline;
                    selected = i;
                }
            }
        }

        // 3. Execute
        if (selected != -1) {
            printf("Time %2d: Task %d runs (Deadline: %d)\n", t, tasks[selected].id, tasks[selected].deadline);
            tasks[selected].remaining--;
        } else {
            printf("Time %2d: Idle\n", t);
        }
    }

    printf("\nSimulation finished at end of 1st cycle (%d).\n", hyperperiod);
    return 0;
}

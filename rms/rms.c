#include <stdio.h>

struct Process {
    int pid;
    int burst;
    int period;
    int remaining;
};

int main() {
    int n, time;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Period: ");
        scanf("%d", &p[i].period);

        p[i].remaining = p[i].burst;
    }

    printf("\nEnter total execution time: ");
    scanf("%d", &time);

    printf("\nRMS Execution:\n");

    // Scheduling
    for (int t = 0; t < time; t++) {

        int highest = -1;

        // Find highest priority process
        for (int i = 0; i < n; i++) {

            // Process arrives at its period
            if (t % p[i].period == 0)
                p[i].remaining = p[i].burst;

            // Select lower period process
            if (p[i].remaining > 0) {
                if (highest == -1 ||
                    p[i].period < p[highest].period) {
                    highest = i;
                }
            }
        }

        // Execute process
        if (highest != -1) {
            printf("Time %d -> P%d\n", t, p[highest].pid);
            p[highest].remaining--;
        }
        else {
            printf("Time %d -> Idle\n", t);
        }
    }

    return 0;
}

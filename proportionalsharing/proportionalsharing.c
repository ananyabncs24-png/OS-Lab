#include <stdio.h>

int main() {
    int n, i;
    int burst[10], share[10];
    float cpuTime[10], totalBurst = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst time and CPU share
    for(i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);

        printf("Enter Burst Time: ");
        scanf("%d", &burst[i]);

        printf("Enter CPU Share (in %%): ");
        scanf("%d", &share[i]);

        totalBurst += burst[i];
    }

    printf("\n--- Proportional Sharing Scheduling ---\n");
    printf("Process\tBurst Time\tCPU Share\tAllocated CPU Time\n");

    for(i = 0; i < n; i++) {
        cpuTime[i] = (share[i] / 100.0) * totalBurst;

        printf("P%d\t%d\t\t%d%%\t\t%.2f\n",
               i + 1,
               burst[i],
               share[i],
               cpuTime[i]);
    }

    return 0;
}

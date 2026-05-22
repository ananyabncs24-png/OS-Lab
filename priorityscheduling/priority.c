#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int pr;   // Priority
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int rt;   // Remaining Time (for preemptive)
};

// 🔹 Non-Preemptive Priority Scheduling
void nonPreemptive(struct Process p[], int n) {
    int completed = 0, time = 0;
    int visited[100] = {0};

    while (completed < n) {
        int idx = -1;
        int highest = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i]) {
                if (p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            visited[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }
}

// 🔹 Preemptive Priority Scheduling
void preemptive(struct Process p[], int n) {
    int completed = 0, time = 0;

    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    while (completed < n) {
        int idx = -1;
        int highest = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].tat = time - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            time++;
        }
    }
}

// 🔹 Display Function
void display(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].pr, p[i].wt, p[i].tat);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

// 🔹 Main Function with Switch Case
int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter Arrival Time, Burst Time and Priority:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
    }

    printf("\nChoose Scheduling Algorithm:");
    printf("\n1. Non-Preemptive Priority");
    printf("\n2. Preemptive Priority");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            nonPreemptive(p, n);
            display(p, n);
            break;

        case 2:
            preemptive(p, n);
            display(p, n);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

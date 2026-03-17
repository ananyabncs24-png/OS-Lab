#include <stdio.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
};

int main()
{
    int n, current_time = 0, completed = 0, min_bt, index;
    float total_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    // Scheduling
    while(completed < n)
    {
        min_bt = 9999;
        index = -1;

        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= current_time && p[i].completed == 0)
            {
                if(p[i].bt < min_bt)
                {
                    min_bt = p[i].bt;
                    index = i;
                }
            }
        }

        if(index == -1)
        {
            current_time++;
        }
        else
        {
            p[index].ct = current_time + p[index].bt;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;

            total_wt += p[index].wt;

            p[index].completed = 1;
            current_time = p[index].ct;
            completed++;
        }
    }

    // Output
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}

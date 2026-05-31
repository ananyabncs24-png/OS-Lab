#include <stdio.h>

#define MAX 10

int main() {
    int p, r;
    int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX];
    int finish[MAX] = {0}, safeSeq[MAX]; //Initialize ALL elements of the array to 0

    printf("Enter number of processes: ");
    scanf("%d", &p);

    printf("Enter number of resources: ");
    scanf("%d", &r);

    printf("\nEnter Allocation Matrix:\n");
    for(int i=0;i<p;i++)
        for(int j=0;j<r;j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Maximum Matrix:\n");
    for(int i=0;i<p;i++)
        for(int j=0;j<r;j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for(int j=0;j<r;j++)
        scanf("%d", &available[j]);

    // NEED matrix
    for(int i=0;i<p;i++)
        for(int j=0;j<r;j++)
            need[i][j] = max[i][j] - allocation[i][j];

    int count = 0;

    while(count < p) {
        int found = 0;

        for(int i=0;i<p;i++) {
            if(!finish[i]) {
                int j;
                for(j=0;j<r;j++) {
                    if(need[i][j] > available[j])
                        break;
                }

                if(j == r) {
                    for(int k=0;k<r;k++)
                        available[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found) {
            printf("\nSystem is NOT in safe state\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state\nSafe sequence: ");
    for(int i=0;i<p;i++)
        printf("P%d ", safeSeq[i]);

    return 0;
}

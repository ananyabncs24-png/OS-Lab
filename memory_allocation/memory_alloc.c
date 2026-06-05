#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFIRST FIT Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int bestIdx = -1;

        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if(bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBEST FIT Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int worstIdx = -1;

        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if(worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWORST FIT Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int m, n, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[m], originalBlocks[m];

    printf("Enter sizes of memory blocks:\n");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &blockSize[i]);
        originalBlocks[i] = blockSize[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processSize[n];

    printf("Enter sizes of processes:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    printf("\nChoose Allocation Method:\n");
    printf("1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            firstFit(blockSize, m, processSize, n);
            break;

        case 2:
            for(int i = 0; i < m; i++)
                blockSize[i] = originalBlocks[i];

            bestFit(blockSize, m, processSize, n);
            break;

        case 3:
            for(int i = 0; i < m; i++)
                blockSize[i] = originalBlocks[i];

            worstFit(blockSize, m, processSize, n);
            break;

        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}

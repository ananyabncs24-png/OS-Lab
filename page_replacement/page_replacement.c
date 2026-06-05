#include <stdio.h>

void FIFO(int pages[], int n, int frames)
{
    int frame[50], faults = 0, index = 0, found;

    for(int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for(int i = 0; i < n; i++)
    {
        found = 0;

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int frames)
{
    int frame[50], time[50];
    int faults = 0, counter = 0;

    for(int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = 0;

            for(int j = 1; j < frames; j++)
            {
                if(time[j] < time[pos])
                    pos = j;
            }

            frame[pos] = pages[i];
            counter++;
            time[pos] = counter;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

void Optimal(int pages[], int n, int frames)
{
    int frame[50];
    int faults = 0;

    for(int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = -1;

            for(int j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
            {
                int farthest = -1;

                for(int j = 0; j < frames; j++)
                {
                    int k;

                    for(k = i + 1; k < n; k++)
                    {
                        if(frame[j] == pages[k])
                            break;
                    }

                    if(k == n)
                    {
                        pos = j;
                        break;
                    }

                    if(k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

int main()
{
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("\nChoose Algorithm:\n");
    printf("1. FIFO\n");
    FIFO(pages, n, frames);
    printf("2. LRU\n");
    LRU(pages, n, frames);
    printf("3. Optimal\n");
    Optimal(pages, n, frames);


    return 0;
}

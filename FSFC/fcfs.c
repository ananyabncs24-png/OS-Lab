#include<stdio.h>

struct process
{
    int at;
    int bt;
    int pid;
    int tat;
    int wt;
    int ct;
}process;

void main()
{
    int n;
    printf("Enter the number opf processes");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        printf("enter at of %d process",i+1);
        scanf("%d",&p[i].at);
        printf("enter bt of %d process",i+1);
        scanf("%d",&p[i].bt);
        printf("enter pid of %d process",i+1);
        scanf("%d",&p[i].pid);
    }
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            struct process temp;
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int current_time=0;
    for(int i=0;i<n;i++)
    {
        if(current_time<p[i].at)
        {
            current_time=p[i].at;
        }
        p[i].ct=current_time+p[i].bt;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        current_time=p[i].ct;
    }
    int swt=0;
    int stat=0;
    for(int i=0;i<n;i++)
    {
        swt=swt+p[i].wt;
        stat=stat+p[i].tat;
    }

    printf("DISPLAYING\n");
    printf("process arrival burst compl turn wait\n");
    for(int i=0;i<n;i++)
    {
        printf("%d      %d      %d      %d     %d      %d",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        printf("\n");
    }
    printf("average wait time: %d",swt/n);
    printf("average turn around time:%d",stat/n);}


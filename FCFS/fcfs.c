#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#define MAX_LEN 10

int main()
{
    int i, j, n;
    float wtavg = 0, tatavg = 0;
    Process process[MAX_LEN];
    printf("Enter number of process: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        process[i].pno = i + 1;
        printf("Process %d: \n", i + 1);
        printf("Enter arrival time: ");
        scanf("%d", &process[i].at);
        printf("Enter burst time: ");
        scanf("%d", &process[i].bt);
    }
    sortProcess(process, 0, n - 1, 0);
    for (i = 0, j = 0; i < n; i++)
    {
        if (i != 0 && process[i].at != process[i - 1].at)
        {
            sortProcess(process, j, i - 1, 1);
            j = i;
        }
    }
    sortProcess(process, j, i - 1, 1);
    process[0].wt = 0;
    tatavg = process[0].tat = process[0].bt;

    for (i = 1; i < n; i++)
    {
        process[i].wt = process[i - 1].tat;
        process[i].tat = process[i].bt + process[i].wt;
        wtavg += process[i].wt;
        tatavg += process[i].tat;
    }

    wtavg /= n;
    tatavg /= n;
    printf("-------------------------------------------\n");
    printf("Process\t\tat\tbt\twt\ttat\n");
    printf("-------------------------------------------\n");
    for (i = 0; i < n; i++)
    {        
        printf("%d\t\t%d\t%d\t%d\t%d\n", process[i].pno, process[i].at, process[i].bt, process[i].wt, process[i].tat);
    }

    printf("Average waiting time: %f\n", wtavg);
    printf("Average turn-around time: %f\n", tatavg);
    return 0;
}

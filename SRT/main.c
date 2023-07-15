#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "queue.h"
#include "sort.h"

#define MAX_LEN 10

int main()
{
    int i, j, n;
    int currTime = 0;
    float wtavg = 0, tatavg = 0;
    Process process[MAX_LEN];
    Process *currProcess = NULL;
    SjfQueue sjfQueue;
    initSjfQueue(&sjfQueue);

    printf("Enter number of process: ");
    scanf("%d", &n);
    while (n > MAX_LEN)
    {
        printf("Max process is %d\n", MAX_LEN);
        printf("Enter again: ");
        scanf("%d", &n);
    }
    for (i = 0; i < n; i++)
    {
        printf("Process %d: \n", i + 1);
        printf("Enter arrival time: ");
        scanf("%d", &process[i].at);
        printf("Enter burst time: ");
        scanf("%d", &process[i].bt);
        process[i].rt = process[i].bt;
        process[i].id = i;
    }
    sortProcess(process, 0, n - 1, 0);
    i = 0;
    while (currTime <= process[n - 1].at || !isEmpty(&sjfQueue))
    {
        while (i < n && currTime == process[i].at)
        {
            // push it to sjf queue
            push(&sjfQueue, &(process[i]));
            i++;
        }
        if (!isEmpty(&sjfQueue))
        {
            currProcess = front(&sjfQueue);
            if (currProcess->rt <= 0)
            {
                currProcess->tat = currTime - currProcess->at;
                pop(&sjfQueue);
                currProcess = front(&sjfQueue);
            }
            if (currProcess)
            {
                currProcess->rt--;
                printf("Time: %d ; Process: P%d\n", currTime, currProcess->id);
            }
        }
        currTime++;
    }

    sortProcess(process, 0, n - 1, 2);

    for (i = 0; i < n; i++)
    {
        process[i].wt = process[i].tat - process[i].bt;
        tatavg += process[i].tat;
        wtavg += process[i].wt;
    }

    tatavg /= n;
    wtavg /= n;

    printf("Order of completion of processes\n");
    printf("Pr\tAt\tBt\tWt\tTat\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", process[i].id, process[i].at, process[i].bt, process[i].wt, process[i].tat);

    printf("Waiting time average: %f\n", wtavg);
    printf("Turn around time average: %f\n", tatavg);
    return 0;
}

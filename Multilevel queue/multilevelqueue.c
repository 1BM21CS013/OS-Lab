#include <stdio.h>
#include "process.h"
#include "processQueue.h"
#include "megaQueue.h"

int main()
{
    int nq, np;
    printf("Enter the number of Queues: ");
    scanf("%d", &nq);
    printf("Enter the number of Process: ");
    scanf("%d", &np);

    MegaQueue mq;
    ProcessQueue wq;
    ProcessQueue pq[nq];
    Process p[np];
    ProcessQueue *currQ;
    Process *currP;
    int pushedCount = 0;
    int queueStatus = 0;
    int time = 0;
    int i, j;

    initMegaQueue(&mq);
    initProcessQueue(&wq);
    for (int i = 0; i < nq; i++)
    {
        initProcessQueue(&pq[i]);
        pq[i].priority = i;
    }
    printf("Enter the arrival time and cpu time and queue number for each process:\n");
    for (int i = 0; i < np; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].cput, &p[i].queue);
        p[i].rt = p[i].cput;
        p[i].pno = i + 1;
    }
    sortProcess(p, 0, np - 1, 0);
    for (i = 0, j = 0; i < np; i++)
    {
        if (i != 0 && p[i].at != p[i - 1].at)
        {
            sortProcess(p, j, i - 1, 1);
            j = i;
        }
    }
    sortProcess(p, j, i - 1, 1);
    // printf("Reached here\n");
    for (int i = 0; i < np; i++)
        pQpush(&wq, &p[i]);
    // printf("Reached here\n");

    // do queue simulation until mega queue or waiting queue is not empty
    while (!isMqEmpty(&mq) || !isPqEmpty(&wq))
    {
        // printf("Reached here\n");
        // check process having arrival time equal to current time
        // push them to respective queues
        // if (isPqEmpty(&wq))
        // printf("Waiting queue is empty\n");
        // if (isMqEmpty(&mq))
        // printf("Mega queue became empty\n");
        while (!isPqEmpty(&wq) && time == pQfront(&wq)->at)
        {
            // printf("Reached inner while\n");
            currP = pQfront(&wq);
            if (isPqEmpty(&pq[currP->queue]))
            {
                // printf("Pushed queue to mega queue\n");
                mQpush(&mq, &pq[currP->queue]);
            }
            pQpush(&pq[currP->queue], currP);
            pQpop(&wq);
        }

        // if mega queue is empty continue and wait for process to enter the queues
        if (isMqEmpty(&mq))
        {
            time++;
            // printf("Continuing\n");
            continue;
        }

        // get the queue in the front from mega queue
        currQ = mQfront(&mq);

        // get the process in the front from current queue
        currP = pQfront(currQ);

        // decrement the remaining time of the current process
        currP->rt--;

        // if remaining time is zero, pop it out from the current queue
        if (currP->rt == 0)
        {
            pQpop(currQ);
            // calculate turnaround time and waiting time
            currP->tat = time - currP->at + 1;
            currP->wt = currP->tat - currP->cput;

            // if current queue became empty, pop it out from mega queue
            if (isPqEmpty(currQ))
            {
                // printf("Queue popped\n");
                // printf("%d %d\n",mq.front,mq.rear);
                mQpop(&mq);
                // printf("%d %d\n",mq.front,mq.rear);
                // if (isMqEmpty(&mq))
                // printf("Mega queue became empty\n");
            }
        }

        // increment timer
        time++;
    }
    printf("\nProcess Stats:\n");
    for (int i = 0; i < np; i++)
    {
        printf("Process %d: at-%d cput-%d tat-%d wt-%d\n", p[i].pno, p[i].at, p[i].cput, p[i].tat, p[i].wt);
    }

    return 0;
}
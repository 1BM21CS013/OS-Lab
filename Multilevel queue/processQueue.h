#define MAX_PROCESS_Q_SIZE 20
typedef struct ProcessQueue
{
    Process *queue[MAX_PROCESS_Q_SIZE];    
    int front;
    int rear;
    int priority;
} ProcessQueue;

void initProcessQueue(ProcessQueue *pq)
{
    pq->front = -1;
    pq->rear = -1;
}

int isPqEmpty(ProcessQueue *pq)
{
    if (pq->front == -1 && pq->rear == -1)
        return 1;
    else 
        return 0;
}

int isPqFull(ProcessQueue *pq)
{
    if (pq->rear == MAX_PROCESS_Q_SIZE - 1)
        return 1;
    else 
        return 0;
}

Process* pQfront(ProcessQueue *pq)
{
    if(!isPqEmpty(pq))
        return pq->queue[pq->front];
    return NULL;
}

void pQpush(ProcessQueue *pq, Process *p)
{
    // push based on priority
    if(isPqEmpty(pq))
    {
        pq->front = 0;
        pq->rear = 0;
        pq->queue[pq->rear] = p;
    }
    else if(!isPqFull(pq))
    {
        pq->rear++;
        pq->queue[pq->rear] = p;
    }
}

void pQpop(ProcessQueue *pq)
{
    if(!isPqEmpty(pq))
    {
        if(pq->front == pq->rear)
            pq->front = pq->rear = -1;
        else
            pq->front++;
    }
}

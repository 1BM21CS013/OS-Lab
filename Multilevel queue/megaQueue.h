#define MAX_MEGA_QUEUE_SIZE 20

typedef struct MegaQueue
{
    ProcessQueue *queue[MAX_MEGA_QUEUE_SIZE];
    int front;
    int rear;
} MegaQueue;

void initMegaQueue(MegaQueue *mq)
{
    mq->front = -1;
    mq->rear = -1;
}

int isMqEmpty(MegaQueue *mq)
{
    if (mq->front == -1 && mq->rear == -1)
        return 1;
    else
        return 0;
}

int isMqFull(MegaQueue *mq)
{
    if (mq->rear == MAX_PROCESS_Q_SIZE - 1)
        return 1;
    else
        return 0;
}

ProcessQueue *mQfront(MegaQueue *mq)
{
    if (!isMqEmpty(mq))
        return mq->queue[mq->front];
    return NULL;
}

void mQpush(MegaQueue *mq, ProcessQueue *pq)
{
    // push based on priority
    if (isMqEmpty(mq))
    {
        mq->front = 0;
        mq->rear = 0;
        mq->queue[mq->rear] = pq;
    }
    else if (!isMqFull(mq))
    {
        int i;
        for (i = mq->rear; i >= mq->front; i--)
        {
            if (mq->queue[i]->priority <= pq->priority)
                break;
            else
                mq->queue[i + 1] = mq->queue[i];
        }
        mq->queue[i + 1] = pq;
        mq->rear++;
    }
}

void mQpop(MegaQueue *mq)
{
    if (!isMqEmpty(mq))
    {
        if (mq->front == mq->rear)
            mq->front = mq->rear = -1;
        else
            mq->front++;
    }
}

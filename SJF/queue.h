#include "process.h"
#define MAX_QUEUE_SIZE 20

typedef struct SjfQueue
{
  int front;
  int rear;
  Process *queue[20];
} SjfQueue;

void initSjfQueue(SjfQueue *q)
{
  q->front = q->rear = -1;
}

int isFull(SjfQueue *q)
{
  if (q->rear == MAX_QUEUE_SIZE - 1)
    return 1;
  else
    return 0;
}

int isEmpty(SjfQueue *q)
{
  if (q->front == q->rear && q->front == -1)
    return 1;
  else
    return 0;
}

// this is a priority queue
void push(SjfQueue *q, Process *p)
{
  if (isEmpty(q))
  {
    q->rear = q->front = 0;
    q->queue[q->rear] = p;
    return;
  }
  else if (!isFull(q))
  {
    int i;
    for (i = q->rear; i >= q->front; i--)
    {
      if (q->queue[i]->bt <= p->bt)
        break;
      else
        q->queue[i + 1] = q->queue[i];
    }
    q->queue[i + 1] = p;
    (q->rear)++;
  }
}

Process *pop(SjfQueue *q)
{
  int temp;
  if (isEmpty(q))
    return NULL;
  else if (q->front == q->rear)
  {
    temp = q->front;
    q->front = q->rear = -1;
    return (q->queue[temp]);
  }
  else if (!isEmpty(q))
    return (q->queue[(q->front)++]);
}

Process *front(SjfQueue *q)
{
  if (!isEmpty(q))
    return (q->queue[q->front]);
  else
    return NULL;
}
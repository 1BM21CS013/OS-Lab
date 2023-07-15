#include "process.h"

void merge(Process *p, int start, int mid, int end, int type)
{
    int n = end - start + 1;
    Process copy[n];
    int i = start, j = mid + 1, k = 0;
    while (i <= mid && j <= end)
    {
        if (type == 0)
            copy[k++] = p[i].at <= p[j].at ? p[i++] : p[j++];
        else if (type == 1)
            copy[k++] = p[i].bt <= p[j].bt ? p[i++] : p[j++];
        else if (type == 2)
            copy[k++] = p[i].tat <= p[j].tat ? p[i++] : p[j++];
    }
    while (i <= mid)
        copy[k++] = p[i++];
    while (j <= end)
        copy[k++] = p[j++];
    for (k = 0; k < n; k++)
        p[k + start] = copy[k];
}

void sortProcess(Process *p, int start, int end, int type)
{
    if (start >= end)
        return;
    int mid = (start + end) / 2;
    sortProcess(p, start, mid, type);
    sortProcess(p, mid + 1, end, type);
    merge(p, start, mid, end, type);
}
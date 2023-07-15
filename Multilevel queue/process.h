typedef struct Process
{
    int pno;
    int at;
    int cput;
    int rt;
    int tat;
    int wt;
    int queue;
} Process;

void merge(Process *p, int start, int mid, int end, int type)
{
    int i = start;
    int j = mid + 1;
    int k = 0;
    Process copy[end - start + 1];
    while (i <= mid && j <= end)
    {
        if (type == 0)
            copy[k++] = p[i].at <= p[j].at ? p[i++] : p[j++];
        else
            copy[k++] = p[i].cput <= p[j].cput ? p[i++] : p[j++];
    }
    while (i <= mid)
        copy[k++] = p[i++];
    while (j <= end)
        copy[k++] = p[j++];

    for (k = 0; k < end - start + 1; k++)
        p[start + k] = copy[k];
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
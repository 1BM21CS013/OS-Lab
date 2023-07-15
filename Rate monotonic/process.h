typedef struct Process
{
    int period;
    int cput;
    int priority;
    int utilTime;
} Process;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    return (a * b / gcd(a, b));
}

int hyperPeriod(Process *p, int n)
{
    int hyperPeriod = 1;
    while (n--)    
        hyperPeriod = lcm(hyperPeriod, p[n].period);            
    return hyperPeriod;
}

float calcCpuUtil(Process *p, int n , int hyperPeriod)
{
    float cpuUtil = 0;
    for(int i = 0 ; i < n ; i++)
    {
        p[i].utilTime = hyperPeriod/p[i].period;
        p[i].utilTime *= p[i].cput;
        cpuUtil += p[i].utilTime;
    }
    return cpuUtil/hyperPeriod;
}

void merge(Process *p, int start, int mid, int end, int type)
{
    int i = 0;
    int j = mid + 1;
    int k = 0;
    Process copy[end - start + 1];
    while (i <= mid && j <= end)
        copy[k++] = p[i].period <= p[j].period ? p[i++] : p[j++];
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
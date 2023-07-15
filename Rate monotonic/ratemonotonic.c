#include <stdio.h>
#include "process.h"
int main()
{
    int n;
    printf("Enter number of process: ");
    scanf("%d", &n);
    Process p[n];
    printf("Enter the period time and cpu time for each process: \n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &p[i].period);
        scanf("%d", &p[i].cput);
    }
    int hyperPeriodVal = hyperPeriod(p, n);
    printf("hyperperiod: %d\n", hyperPeriodVal);
    printf("CPU Utilization: %0.2f\n", calcCpuUtil(p, n, hyperPeriodVal));
    return 0;
}
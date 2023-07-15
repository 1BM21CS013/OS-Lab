typedef struct Process
{
    int id;  /* process id. */
    int bt;  /* burst time - duration taken to complete the process. */
    int at;  /* arrival time - time at which process arrived. */
    int wt;  /* wait time - total wait duration. */
    int tat; /* turn around time - total duration from arrival time to exit time. */
    int rt;  /* remaining time - remaining time for completing execution. */
} Process;


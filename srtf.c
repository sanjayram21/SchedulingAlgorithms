#include <stdio.h>
#include <stdlib.h>
typedef struct item
{
    int processNo;
    int arrivalTime;
    int burstTime;
    int curBurstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int seen;
} item;

int compare(const void *a, const void *b)
{
    item *itema = (item *)a;
    item *itemb = (item *)b;
    if (itema->curBurstTime == itemb->curBurstTime)
        return itema->arrivalTime - itemb->arrivalTime;
    return itema->curBurstTime - itemb->curBurstTime;
}

int compareByArrivalTime(const void *a, const void *b)
{
    item *itema = (item *)a;
    item *itemb = (item *)b;
    return itema->arrivalTime - itemb->arrivalTime;
}

int main()
{
    printf("Enter number of processes\n");
    int n;
    scanf("%d", &n);
    item arr[100];
    printf("Enter arrival time and burst time for %d processes\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i].arrivalTime, &arr[i].burstTime);
        arr[i].curBurstTime = arr[i].burstTime;
        arr[i].processNo = i + 1;
        arr[i].seen = 0;
    }
    qsort(arr, n, sizeof(item), compare);
    int turnAroundTime = 0;
    int waitingTime = 0;
    int curTime = 0;
    int seen = 0;
    while (seen < n)
    {
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i].seen == 1)
                continue;
            if (arr[i].arrivalTime <= curTime)
            {
                curTime++;
                arr[i].curBurstTime--;
                if (arr[i].curBurstTime == 0)
                {
                    arr[i].seen = 1;
                    arr[i].completionTime = curTime;
                    arr[i].turnAroundTime = arr[i].completionTime - arr[i].arrivalTime;
                    arr[i].waitingTime = arr[i].turnAroundTime - arr[i].burstTime;
                    arr[i].seen = 1;
                    turnAroundTime += arr[i].turnAroundTime;
                    waitingTime += arr[i].waitingTime;
                    seen++;
                }
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            curTime++;
        qsort(arr, n, sizeof(item), compare);
    }
    qsort(arr, n, sizeof(item), compareByArrivalTime);
    printf("Process No \t Arrival time \t Burst time \t Completion time \t TAT \t WT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t%d\n", arr[i].processNo, arr[i].arrivalTime, arr[i].burstTime, arr[i].completionTime, arr[i].turnAroundTime, arr[i].waitingTime);
    }
    printf("Average turn around time : %f\nAverage waiting time : %f", (double)turnAroundTime / n, (double)waitingTime / n);
}
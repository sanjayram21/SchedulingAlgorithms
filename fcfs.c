#include <stdio.h>
#include <stdlib.h>
typedef struct item
{
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
} item;

int compare(const void *a, const void *b)
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
    }
    qsort(arr, n, sizeof(item), compare);
    printf("Arrival time\tBurst time\n");
    int turnAroundTime = 0;
    int waitingTime = 0;
    int curTime = 0;
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\n", arr[i].arrivalTime, arr[i].burstTime);
        if (arr[i].arrivalTime > curTime)
        {
            curTime = arr[i].arrivalTime;
        }
        curTime += arr[i].burstTime;
        arr[i].completionTime = curTime;
        arr[i].turnAroundTime = arr[i].completionTime - arr[i].arrivalTime;
        arr[i].waitingTime = arr[i].turnAroundTime - arr[i].burstTime;
        turnAroundTime += arr[i].turnAroundTime;
        waitingTime += arr[i].waitingTime;
    }
    printf("Arrival time \t Burst time \t Completion time \t TAT \t WT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t\t%d\t\t%d\n", arr[i].arrivalTime, arr[i].burstTime, arr[i].completionTime, arr[i].turnAroundTime, arr[i].waitingTime);
    }
    printf("Average turn around time : %f\nAverage waiting time : %f", (double)turnAroundTime / n, (double)waitingTime / n);
}
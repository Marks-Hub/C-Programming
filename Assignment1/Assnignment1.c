#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum States
{
    New,
    Reedy,
    Running
} States;
struct processblock
{
    int processId;
    int userId;
    int arrivalTime; // time units in simulation, not actual time
    int priority;    // base priority
    int expectedTimeRemaining;
    int expectedMemoryNeed;
    int expectedPctCPU; // to get an idea of whether CPU bound or IO bound
    bool realTime;      // 0 or 1 - whether a real-time process or not (real-time

    States processState;          // Not input - initially NEW
    int currentPriority;          // can be increased or lowered based on what has happened with the process - not input - initially same as base priority
    int timeWaitingSoFar;         // Not input - initially zero
    int timeProcessingLastRun;    // Not input - initially zero
    int timeProcessingSoFar;      // Not input - initially zero
    struct processblock *nextPtr; // not used in this program
};

int main(void)
{
    char entire_row1[8];
    int processId;
    int userId;
    int arrivalTime; // time units in simulation, not actual time
    int priority;    // base priority
    int expectedTimeRemaining;
    int expectedMemoryNeed;
    int expectedPctCPU; // to get an idea of whether CPU bound or IO bound
    int realTime;
    int i = 0, r;

    FILE *fp;
    fp = fopen("allprocesses.txt", "r");
    if (fp == NULL)
    {
        printf("File does not exist");
        exit(1);
    }

    while ((r = fscanf(fp, "%d %d %d %d %d %d", &processId, &userId, &arrivalTime, &priority, &expectedTimeRemaining, &expectedMemoryNeed)) != EOF)
    {
        fscanf(fp, "%d", &expectedPctCPU);
        fscanf(fp, "%d", &realTime);
        // printf ("%d %d\n", expectedMemoryNeed, expectedPctCPU);

        if (r == 6)
        { // Do we get the 6 matches of "%d %d"?
            i++;

            struct processblock pcb;
            pcb.processId = processId;
            pcb.userId = userId;
            pcb.arrivalTime = arrivalTime;
            pcb.priority = priority;
            pcb.expectedTimeRemaining = expectedTimeRemaining;
            pcb.expectedMemoryNeed = expectedMemoryNeed;
            pcb.expectedPctCPU = expectedPctCPU;
            pcb.realTime = realTime;

            // printf("%d", pcb.expectedPctCPU);

            if (pcb.priority == 1)
            {
                printf("ID: %d  USer: %d  Arr: %d  Pri: %d  Remain: %d  Mem: %d  CPU: %d \n", pcb.processId, pcb.userId, pcb.arrivalTime, pcb.priority, pcb.expectedTimeRemaining, pcb.expectedMemoryNeed, pcb.expectedPctCPU);
            }
            /* printf("processId: \t\t%d\n", processId);
             printf("userId: \t\t%d\n", userId);
             printf("arrivalTime: \t\t%d\n", arrivalTime);
             printf("priority: \t\t%d\n", priority);
             printf("expectedTimeRemaining: \t\t%d\n", expectedTimeRemaining);
             printf("expectedMemoryNeed: \t\t%d\n", expectedMemoryNeed);
             printf("expectedPctCPU: \t\t%d\n", expectedPctCPU);
             printf("realTime: \t\t%d\n", realTime); */
        }
    }

    fclose(fp);

    return 0;
}
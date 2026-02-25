//Name: Alex Solomon
//Date: 2/24/2026
//Assignment: CS470 - Lab 4: Shortest Job First (SJF) Scheduling Algorithm (Preemptive / SRTF)


//Include statements
#include <stdio.h>
#include <limits.h>

//Process structure
typedef struct 
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

//Main function
int main()
{
    //Variables
    int numProcesses;
    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    Process processes[20];

    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].id = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completion_time = 0;
    }

    //Track execution order
    int execution_order[1000];
    int exec_count = 0;

    int completed = 0;
    int currentTime = 0;

    //Preemptive SJF (Shortest Remaining Time First)
    while (completed < numProcesses)
    {
        //Find process with shortest remaining time among arrived processes
        int shortest = -1;
        int min_remaining = INT_MAX;

        for (int i = 0; i < numProcesses; i++)
        {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0)
            {
                if (processes[i].remaining_time < min_remaining)
                {
                    min_remaining = processes[i].remaining_time;
                    shortest = i;
                }
                else if (processes[i].remaining_time == min_remaining && shortest != -1)
                {
                    //Tie-break by arrival time
                    if (processes[i].arrival_time < processes[shortest].arrival_time)
                    {
                        shortest = i;
                    }
                }
            }
        }

        if (shortest == -1)
        {
            //No process available, advance time
            currentTime++;
            continue;
        }

        //Record execution order
        execution_order[exec_count++] = processes[shortest].id;

        //Execute for 1 time unit (preemptive)
        processes[shortest].remaining_time--;
        currentTime++;

        //Check if process is complete
        if (processes[shortest].remaining_time == 0)
        {
            completed++;
            processes[shortest].completion_time = currentTime;
            processes[shortest].turnaround_time = currentTime - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            total_waiting_time += processes[shortest].waiting_time;
            total_turnaround_time += processes[shortest].turnaround_time;
        }
    }

    //Print execution order (condensed - consecutive same process shown once)
    printf("\nExecution Order: ");
    for (int i = 0; i < exec_count; i++)
    {
        if (i == 0 || execution_order[i] != execution_order[i - 1])
        {
            if (i > 0) printf(" -> ");
            printf("P%d", execution_order[i]);
        }
    }
    printf("\n");

    //Print results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < numProcesses; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / numProcesses);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / numProcesses);

    return 0;
}
//Name: Alex Solomon
//Date: 2/24/2026
//Assignment: CS470 - Lab 4: Round Robin (RR) Scheduling Algorithm


//Include statements
#include <stdio.h>

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
    int in_queue;
} Process;

//Main function
int main()
{
    //Variables
    int numProcesses, time_quantum;
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
        processes[i].in_queue = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    //Ready queue
    int queue[1000];
    int front = 0, rear = 0;

    //Track execution order
    int execution_order[1000];
    int exec_count = 0;

    int currentTime = 0;
    int completed = 0;

    //Sort processes by arrival time
    for (int i = 0; i < numProcesses - 1; i++)
    {
        for (int j = i + 1; j < numProcesses; j++)
        {
            if (processes[j].arrival_time < processes[i].arrival_time)
            {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    //Add processes that arrive at time 0 to the queue
    for (int i = 0; i < numProcesses; i++)
    {
        if (processes[i].arrival_time <= 0)
        {
            queue[rear++] = i;
            processes[i].in_queue = 1;
        }
    }

    //Round Robin scheduling with arrival times
    while (completed < numProcesses)
    {
        if (front == rear)
        {
            //Queue is empty, advance time to next arrival
            currentTime++;
            for (int i = 0; i < numProcesses; i++)
            {
                if (!processes[i].in_queue && processes[i].remaining_time > 0 && processes[i].arrival_time <= currentTime)
                {
                    queue[rear++] = i;
                    processes[i].in_queue = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        //Record execution order
        execution_order[exec_count++] = processes[idx].id;

        //Execute for time quantum or remaining time, whichever is smaller
        int exec_time;
        if (processes[idx].remaining_time > time_quantum)
        {
            exec_time = time_quantum;
        }
        else
        {
            exec_time = processes[idx].remaining_time;
        }

        currentTime += exec_time;
        processes[idx].remaining_time -= exec_time;

        //Add newly arrived processes to queue (arrived during this execution)
        for (int i = 0; i < numProcesses; i++)
        {
            if (!processes[i].in_queue && processes[i].remaining_time > 0 && processes[i].arrival_time <= currentTime)
            {
                queue[rear++] = i;
                processes[i].in_queue = 1;
            }
        }

        if (processes[idx].remaining_time == 0)
        {
            //Process completed
            completed++;
            processes[idx].completion_time = currentTime;
            processes[idx].turnaround_time = currentTime - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            total_waiting_time += processes[idx].waiting_time;
            total_turnaround_time += processes[idx].turnaround_time;
        }
        else
        {
            //Put back in queue
            queue[rear++] = idx;
        }
    }

    //Print execution order
    printf("\nExecution Order: ");
    for (int i = 0; i < exec_count; i++)
    {
        if (i > 0) printf(" -> ");
        printf("P%d", execution_order[i]);
    }
    printf("\n");

    //Print results (sorted by process ID)
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int id = 1; id <= numProcesses; id++)
    {
        for (int i = 0; i < numProcesses; i++)
        {
            if (processes[i].id == id)
            {
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time,
                       processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
                break;
            }
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / numProcesses);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / numProcesses);

    return 0;
}
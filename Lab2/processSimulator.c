//Name: Alex Solomon
//Date: 2/2/2026
//Assignment: CS470 Lab 2 - Process Simulator

//Include statements
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

//Compile-time constant (prevents VLA initialization error)
#define NUMBER_OF_CHILDREN 15

//Driver Function
int main()
{
    //Local variables and constants
    pid_t childPid[NUMBER_OF_CHILDREN];
    pid_t pid;
    int status;

    //Summary counters
    int normalExitZero = 0;
    int normalExitNonZero = 0;
    int terminatedBySignal = 0;

    //Parent information
    printf("Parent Process: My PID is %d\n\n", getpid());

    //Command list: 15 entries
    //Children 13 and 14 will call abort() after printing the details.
    char *commands[NUMBER_OF_CHILDREN][6] =
    {
        {"echo", "Hello, Alex Solomon", NULL, NULL, NULL, NULL},
        {"ls", NULL, NULL, NULL, NULL, NULL},
        {"date", NULL, NULL, NULL, NULL, NULL},
        {"pwd", NULL, NULL, NULL, NULL, NULL},
        {"whoami", NULL, NULL, NULL, NULL, NULL},
        {"uname", "-a", NULL, NULL, NULL, NULL},
        {"id", NULL, NULL, NULL, NULL, NULL},
        {"sleep", "1", NULL, NULL, NULL, NULL},
        {"printenv", NULL, NULL, NULL, NULL, NULL},
        {"hostname", NULL, NULL, NULL, NULL, NULL},
        {"uptime", NULL, NULL, NULL, NULL, NULL},
        {"df", "-h", NULL, NULL, NULL, NULL},
        {"free", "-h", NULL, NULL, NULL, NULL},
        {"ps", NULL, NULL, NULL, NULL, NULL},
        {"who", NULL, NULL, NULL, NULL, NULL}
    };

    //Two children intentionally run invalid commands
    const int invalidChildA = 11;
    const int invalidChildB = 12;

    //Initialize childPid array
    for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
    {
        childPid[i] = -1;
    }

    //Create children
    for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            //Child process
            //Override commands for invalid exec demonstration
            if (i == invalidChildA)
            {
                commands[i][0] = "invalid_command_one";
                commands[i][1] = NULL;
            }
            else if (i == invalidChildB)
            {
                commands[i][0] = "invalid_command_two";
                commands[i][1] = NULL;
            }

            //Child details
            printf("Child Process: Index=%d, PID=%d\n", i, getpid());
            printf("Child Process: Command=");
            for (int k = 0; commands[i][k] != NULL; k++)
            {
                printf("%s ", commands[i][k]);
            }
            printf("\n");

            //Abort demonstration: signal based
            if (i == 13 || i == 14)
            {
                printf("Child Process: Calling abort() now.\n\n");
                abort();
            }

            //Execute command
            execvp(commands[i][0], commands[i]);

            //If Exec failed
            perror("execvp failed");
            exit(127);
        }
        else
        {
            //Parent process
            childPid[i] = pid;
            printf("Parent Process: Created child index %d with PID=%d\n", i, (int)pid);
        }
    }

    printf("\nParent Process: All children created. Waiting in creation order...\n\n");

    //Wait for children in creation order
    for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
    {
        pid_t w = waitpid(childPid[i], &status, 0);

        if (w == -1)
        {
            perror("waitpid failed");
            continue;
        }

        printf("Parent Process: Child index %d (PID=%d) finished -> ", i, (int)childPid[i]);

        //If exited normally
        if (WIFEXITED(status))
        {
            int code = WEXITSTATUS(status);
            printf("Exited Normally, Exit Code=%d\n", code);

            if (code == 0)
            {
                normalExitZero++;
            }
            else
            {
                normalExitNonZero++;
            }
        }
        //If terminated by signal
        else if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            printf("Terminated by Signal, Signal Number=%d\n", sig);
            terminatedBySignal++;
        }
        //If ended in unexpected state?
        else
        {
            printf("Ended in an unexpected state (status=%d)\n", status);
        }
    }

    //Summary output
    printf("\n================ Parent Summary ================\n");
    printf("Parent PID: %d\n", getpid());
    printf("Children Created: %d\n", NUMBER_OF_CHILDREN);
    printf("Exited Normally (Exit Code 0): %d\n", normalExitZero);
    printf("Exited Normally (Non-Zero Exit Code): %d\n", normalExitNonZero);
    printf("Terminated by Signal: %d\n", terminatedBySignal);
    printf("================================================\n");

    //return success
    return 0;
}

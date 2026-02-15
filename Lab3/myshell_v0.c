//Name: Alex Solomon
//Date: 2/14/2026
//Assignment: CS470 Lab3 - Simple Shell Script

//Include Statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Additional headers for process control and file operations
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//Global Constants
#define MAX_LINE 1024  

//Main Function
int main() 
{
    //Local Variables
    char line[MAX_LINE];
    
    //While true do
    while (1) 
    { 
        printf("myshell> ");
        fflush(stdout);      
        
        // Read a line of input from the user
        if (!fgets(line, sizeof(line), stdin))
            break;   
        line[strcspn(line, "\n")] = 0;

        // Skip empty lines
        if (strlen(line) == 0)
            continue;

        // ============================================
        // TODO: Students implement the following:
        //==============================================
        // 1. Parse the input line into tokens
        //    - Split by whitespace
        //    - Handle special characters (<, >, >>)
        
        //Arguments array and index variable for tokenization
        char *args[MAX_LINE / 2 + 1];
        int i = 0;
        char *ptr = line;

        //Break line into tokens and store in args array
        while (*ptr) 
        {
            //Skip whitespaces
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            
            //If at end of line, break
            if (*ptr == '\0') break;

            //Check for quotation marks
            if (*ptr == '"') 
            {
                ptr++; //Move past the opening quote
                args[i++] = ptr;

                //Find the closing quote
                while (*ptr && *ptr != '"') ptr++;
            } 
            else 
            {
                //Normal token; add to our args array!
                args[i++] = ptr;

                //Find the next whitespace or end of line
                while (*ptr && *ptr != ' ' && *ptr != '\t') ptr++;
            }

            //If not at end of line, null terminate and move to next char
            if (*ptr) 
            {
                *ptr = '\0';
                ptr++;
            }
        }
        args[i] = NULL; //Null term the args array
        
        
        //=============================================
        // 2. Check for built-in commands
        //    - "cd [dir]" - change directory
        //    - "exit" - exit the shell
       
        //Check for exit conditions
        if (args[0] != NULL && strcmp(args[0], "exit") == 0)
        {
            break;
        }
        else if (args[0] != NULL && strcmp(args[0], "cd")==0)
        {
            if (args[1] == NULL) //Error handling for missing directory argument
            {
                //Change to home directory if no argument is provided
                char *home = getenv("HOME");
                if (home != NULL) 
                {
                    chdir(home);
                }
                else
                {
                fprintf(stderr, "Error: 'cd' needs a directory argument!\n");//No home dir found. Rare but possible
                }
            }
            else if (chdir(args[1])!=0) //Error handling for chdir
            {
                perror("An error changing directory. Please check the directory name and try again.");
            }
        } 


        //============================================
        // 3. Execute external commands
        //    - fork() to create child process
        //    - execvp() to run the command
        //    - waitpid() to wait for completion
        else
        {
            pid_t pid = fork(); //Create child process
            if (pid < 0)
            {
                perror("Process creation failed");
            }
            else if (pid == 0) 
            {
                //Loop through args array to find "<", ">", or ">>"
                for (int j = 0; args[j] != NULL; j++) 
                {
                    
                    if (strcmp(args[j], ">") == 0) 
                    {
                        //Open the file for writing
                        int fd = open (args[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

                        //map STDOUT_FILENO to the file descriptor using dup2
                        dup2(fd, STDOUT_FILENO);
                        close(fd);

                        //set index to null to help execvp
                        args[j] = NULL;
                    } 
                    else if (strcmp(args[j], ">>") == 0) 
                    {
                        //Open the file for appending
                        int fd = open(args[j+1], O_WRONLY | O_CREAT | O_APPEND, 0644);

                        //map STDOUT_FILENO to the file descriptor using dup2
                        dup2(fd, STDOUT_FILENO);
                        close(fd);

                        //set index to null to help execvp
                        args[j] = NULL;
                    } 
                    else if (strcmp(args[j], "<") == 0) 
                    {
                        //Open the file for reading
                        int fd = open(args[j+1], O_RDONLY);

                        //map STDIN_FILENO to the file descriptor using dup2
                        dup2(fd, STDIN_FILENO);
                        close(fd);

                        //set index to null to help execvp
                        args[j] = NULL;
                    }
                }

                //Call execvp to execute the command with arguments
                if (execvp(args[0], args) == -1) 
                {
                    perror("Execution failed");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                waitpid(pid, NULL, 0); //If checks pass, wait for child process to finish
            }
        }
        // ============================================
        // For now, just echo back what the user typed
        //printf("[DEBUG] You entered: %s\n", line);
        //printf("[DEBUG] Command not executed (parsing not implemented)\n");
    }
    printf("\nGoodbye!\n");
    return 0;
}
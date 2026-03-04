//Name: Alex Solomon
//Date: 3/3/2026
//Assignment: CS470 - Lab 5: User Level File System Library
//File: Alex_testFC.c

//----------------------------------
//Include Statements
//----------------------------------
#include "Alex_libFC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Driver
int main() 
{
    //Variables
    int userChoice = 0;
    int currentFileDescriptor = -1;
    char targetFileName[] = "Alex Solomon_Introduction.txt";
    char readBuffer[1024];
    
    //Two-paragraph introduction meeting the 3-4 sentence minimum requirement
    char introductionText[] = 
        "Hello, my name is Alex Solomon. I am interested in ethical hacking, penetration testing, and exploring operating systems like Kali Linux.\n\n"
        "I enjoy PC gaming and working on personal programming projects in languages like C and Java. I am excited to build this user file system to better understand how disk operations work.";

    while (userChoice != 7) 
    {
        //Display menu
        printf("\n========================================\n");
        printf("               libFS Menu      \n");
        printf("========================================\n");
        printf("1. Create File (%s)\n", targetFileName);
        printf("2. Open File\n");
        printf("3. Write Introduction to File\n");
        printf("4. Read File Contents\n");
        printf("5. Close File\n");
        printf("6. Delete File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        //Input validation for menu
        if (scanf("%d", &userChoice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }

        //Handle user choice
        switch (userChoice) 
        {
            case 1:
                printf("\n[Attempting to create file...]\n");
                if (fileCreate(targetFileName) == 0) 
                {
                    printf("SUCCESS: File '%s' created successfully.\n", targetFileName);
                } 
                else 
                {
                    printf("ERROR: Failed to create file '%s'.\n", targetFileName);
                }
                break;

            case 2:
                printf("\n[Attempting to open file...]\n");
                currentFileDescriptor = fileOpen(targetFileName);
                if (currentFileDescriptor >= 0) 
                {
                    printf("SUCCESS: File opened successfully. Descriptor: %d\n", currentFileDescriptor);
                } 
                else 
                {
                    printf("ERROR: Failed to open file. It may not exist yet.\n");
                }
                break;

            case 3:
                printf("\n[Attempting to write to file...]\n");
                if (currentFileDescriptor < 0) 
                {
                    printf("ERROR: No file is currently open. Please open the file first.\n");
                } 
                else 
                {
                    int bytesToWrite = strlen(introductionText);
                    int bytesWritten = fileWrite(currentFileDescriptor, introductionText, bytesToWrite);
                    if (bytesWritten == bytesToWrite) 
                    {
                        printf("SUCCESS: Wrote %d bytes to the file.\n", bytesWritten);
                    } 
                    else 
                    {
                        printf("ERROR: Write operation failed or was incomplete.\n");
                    }
                }
                break;

            case 4:
                printf("\n[Attempting to read from file...]\n");
                if (currentFileDescriptor < 0) 
                {
                    printf("ERROR: No file is currently open. Please open the file first.\n");
                } 
                else 
                {
                    //Clear the buffer before reading to prevent leftover data from previous reads
                    memset(readBuffer, 0, sizeof(readBuffer)); 
                    int bytesRead = fileRead(currentFileDescriptor, readBuffer, sizeof(readBuffer) - 1);
                    
                    if (bytesRead >= 0) 
                    {
                        printf("SUCCESS: Read %d bytes from the file. Contents:\n\n", bytesRead);
                        printf("----------------------------------------\n");
                        printf("%s\n", readBuffer);
                        printf("----------------------------------------\n");
                    } 
                    else 
                    {
                        printf("ERROR: Failed to read from the file.\n");
                    }
                }
                break;

            case 5:
                printf("\n[Attempting to close file...]\n");
                if (currentFileDescriptor < 0) 
                {
                    printf("ERROR: No file is currently open to close.\n");
                } 
                else 
                {
                    if (fileClose(currentFileDescriptor) == 0) 
                    {
                        printf("SUCCESS: File closed successfully.\n");
                        currentFileDescriptor = -1; // Reset descriptor after closing
                    } 
                    else 
                    {
                        printf("ERROR: Failed to close the file.\n");
                    }
                }
                break;

            case 6:
                printf("\n[Attempting to delete file...]\n");
                if (fileDelete(targetFileName) == 0) 
                {
                    printf("SUCCESS: File '%s' deleted successfully.\n", targetFileName);
                } 
                else 
                {
                    printf("ERROR: Failed to delete file. Ensure it exists and is not locked.\n");
                }
                break;

            case 7:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Please select an option from 1 to 7.\n");
        }
    }

    //Exit successfully
    return 0;
}
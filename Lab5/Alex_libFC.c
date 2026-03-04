//Name: Alex Solomon
//Date: 3/3/2026
//Assignment: CS470 - Lab 5: User Level File System Library
//File: Alex_libFC.c

//----------------------------------
//Include Statements
//----------------------------------
#include "Alex_libFC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

//----------------------------------
//Function Definitions
//----------------------------------

//Create file function
int fileCreate(char* fileName) 
{
    int fileDescriptor = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fileDescriptor < 0) 
    {
        return -1;
    }
    close(fileDescriptor);
    return 0;
}

//Open file function
int fileOpen(char* fileName)
{
    int fileDescriptor = open(fileName, O_RDWR);
    if (fileDescriptor < 0) 
    {
        return -1;
    }
    return fileDescriptor;
}

//Read file function
int fileRead(int fileDescriptor, char* readBuffer, int bytesToRead)
{
    int bytesReadCount = read(fileDescriptor, readBuffer, bytesToRead);
    if (bytesReadCount < 0)
    {
        return -1;
    }
    return bytesReadCount;
}

//Write file function
int fileWrite(int fileDescriptor, char* writeBuffer, int bytesToWrite)
{
    int bytesWrittenCount = write(fileDescriptor, writeBuffer, bytesToWrite);
    if (bytesWrittenCount < 0)
    {
        return -1;
    }
    return bytesWrittenCount;
}

//Close file function
int fileClose(int fileDescriptor)
{
    if (close(fileDescriptor) < 0)
    {
        return -1;
    }
    return 0;
}

//Delete file function
int fileDelete(char* fileName)
{
    if (unlink(fileName) < 0)
    {
        return -1;
    }
    return 0;
}
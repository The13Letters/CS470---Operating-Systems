//Definitions
#ifndef ALEX_LIBFC_H
#define ALEX_LIBFC_H

//Function Prototypes
int fileCreate(char* fileName);
int fileOpen(char* fileName);
int fileRead(int fileDescriptor, char* readBuffer, int bytesToRead);
int fileWrite(int fileDescriptor, char* writeBuffer, int bytesToWrite);
int fileClose(int fileDescriptor);
int fileDelete(char* fileName);

#endif //ALEX_LIBFC_H
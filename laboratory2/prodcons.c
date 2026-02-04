/*
EPI GIJÓN - University of Oviedo
DEGREE IN COMPUTER SCIENCE/ENGINEERING
DISTRIBUTED SYSTEMS - 3rd YEAR
COURSE MATERIAL
-------------------------
MECHANISM : PIPES
FILE : prodcons.c
DESCRIPTION : We propose the realization of a program in which two processes send to each other through a pipe a text file where the one that receives must show it by its standard output.
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define SUCCESS_CODE 0
#define ERROR_CODE -1

int main(int argc, char **argv)
{
    int fds[2];
    
    // Create a pipe
    // TODO
    pipe(fds);
    
    // This process should send the file to the other process through the pipe
    if (fork() == 0)
    {
        // TODO
        dup2(fds[1], 1);
        close(fds[0]);
        char buffer[50];
        const int fd = open("/home/uo318641/laboratory2/input.txt", O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        write(fds[1], buffer, sizeof(buffer));
    }

    // This other process is in charge of obtaining the pipe file and displaying it as standard output
    else if (fork() == 0)
    {
        // TODO
        dup2(fds[0], 0);
        close(fds[1]);
        char buffer[50];
        read(fds[0], buffer, sizeof(buffer));
        write(STDOUT_FILENO, buffer, sizeof(buffer));
    }

    // The parent closes both descriptors of the pipe and waits for his children.
    else
    {
        // TODO
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
        printf("test");

    }

    return 0;
}
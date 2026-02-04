/*
EPI GIJÓN - University of Oviedo
DEGREE IN COMPUTER SCIENCE/ENGINEERING
DISTRIBUTED SYSTEMS - 3rd YEAR
COURSE MATERIAL
-------------------------
MECHANISM : PIPES
FILE : whosort.c
DESCRIPTION : Implementation of the user process who | sort using pipes
*/

#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fds[2];
    pipe(fds); // Create a pipe

    // The first child reconnects its standard input (stdin) to the output stream of the pipe and closes the descriptor of the pipe input
    if (fork() == 0)
    {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("sort", "sort", NULL);
    }

    // The second child reconnects its standard output (stdout) to the pipe input and closes the descriptor of the pipe output.
    else if (fork() == 0)
    {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("who", "who", NULL);
    }

    // The parent will close both descriptors of the pipe and wait for the completion of its children.
    else
    {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }

    return 0;
}

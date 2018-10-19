#include "csapp.h"

int main(int argc, char **argv, char **envp)
{
    setenv("COLUMNS", "20", 1);
    printf("%s\n", getenv("COLUMNS"));
    execve("/bin/ls", argv, environ);
    printf("\n\n");

    exit(0);
}
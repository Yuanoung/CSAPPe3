/* $begin myecho */
#include "csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    int i;
    // printf("Command-line arguments:\n");
    // for (i = 0; argv[i] != NULL; i++)
    //     printf("    argv[%2d]: %s\n", i, argv[i]);

    printf("\n");
    if (setenv("COLUMNS", "80", 0) == -1)
        printf("error\n");
    printf("Environment variables:\n");
    i = 0;
    while (environ[i])
    {
        printf("environ[%2d]: %s\n", i, environ[i]);
        i++;
    }

    // while (*argv)
    //     printf("%s\n", *argv++);

    // printf("\n");
    // while (*envp)
    //     printf("%s\n", *envp++);

        // while (*envp)
    //     printf("%s\n", *envp++);

    exit(0);
}
/* $end myecho */

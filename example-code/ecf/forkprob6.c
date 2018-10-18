/* $begin forkprob6 */
#include "csapp.h"

void doit()
{
    if (Fork() == 0)
    {
        Fork();
        printf("hello\n");
        return;
    }
    // while (waitpid(-1, NULL, 0) != -1)
    //     ;
    return;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}
/* $end forkprob6 */

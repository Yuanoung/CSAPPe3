/* $begin forkprob2 */
#include "csapp.h"

void end(void)
{
    printf("2\n");
    fflush(stdout);
}

int main()
{
    if (Fork() == 0)
        atexit(end);
    if (Fork() == 0)
    {
        printf("0\n");
        fflush(stdout);
    }
    else
    {
        printf("1\n");
        fflush(stdout);
    }
    exit(0);
}
/* $end forkprob2 */

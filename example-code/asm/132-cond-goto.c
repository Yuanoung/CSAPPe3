void cond(long a, long *p)
{
    if (!p)
        goto FALSE;
    if (*p >= a)
        goto FALSE;
    *p = a;
FALSE:;
}
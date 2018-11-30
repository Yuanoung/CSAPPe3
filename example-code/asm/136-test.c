long test(long x, long y)
{
    long val = 8 * x;
    if (y)
    {
        if (x >= y)
        {
            val = x & y;
        }
        else
            val = y - x;
    }
    else if (y <= -2)
    {
        val = x + y;
    }

    return val;
}
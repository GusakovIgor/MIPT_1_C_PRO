#include <stdio.h>
main()
{
    int c, t;
    c = 0;
    t = 0;
    while ((c != EOF) & (t != EOF))
        c = c + 1;
        t = t - 1;
    if (t == EOF)
        c = t;
    printf ("EOF is %d", c);
}

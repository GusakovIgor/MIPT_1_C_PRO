#include <stdio.h>
#define START 0
main()
{
    long s, t, nl, count;
    int c;
    s = START;
    t = START;
    nl = START;

    while ((c = getchar()) != '*')
        {
        if (c == ' ')
            ++s;
        if (c == '\t')
            ++t;
        if (c == '\n')
            ++nl;
        }
    count = s + t + nl;
    printf("Spaces: %d\nTabulations: %d\nNew strings: %d", s, t, nl);
}

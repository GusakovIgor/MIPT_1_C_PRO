#include <stdio.h>
main()
{
    int c;
    while ((c = getchar()) != '*')
        if (c == ' ')
            putchar('\n');
        else
            putchar(c);
}

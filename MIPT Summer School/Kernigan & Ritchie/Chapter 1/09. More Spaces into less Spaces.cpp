#include <stdio.h>
main()
{
    int c;
    while ((c = getchar()) != '*'){
        if (c == ' ')
            putchar(' ');
        while (c == ' ')
            c = getchar();
        putchar(c);
    }
}

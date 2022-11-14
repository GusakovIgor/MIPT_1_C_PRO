#include <stdio.h>
main()
{
    int c, count;

    while ((c = getchar()) != '*'){
        count = 0;
        if (c == '\t'){
            printf("\\t");
            count++;
        }
        if (c == '\b'){
            printf("\\b");
            count++;
        }
        if (c == '\\'){
            printf("\\\\");
            count++;
        }
        if (count == 0)
            putchar(c);
    }
}

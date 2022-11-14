#include <stdio.h>
main()
{
    int c;
    c = getchar();
    putchar(c);
    printf("\nc connot be EOF (negative integer), cause c contains code of one (first) symbol, which is positive: %d", c);
}

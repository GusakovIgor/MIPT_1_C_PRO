#include <stdio.h>
main()
{
    int c;
    c = (getchar()) != EOF;
    printf ("c is %d\n", c);
    printf ("Not putchar(), because it gives: ");
    putchar (c);
}

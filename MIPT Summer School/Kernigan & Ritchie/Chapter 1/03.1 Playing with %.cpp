#include <stdio.h>
main()
{
    int t;
    t = 1234;
    printf ("%2d%8d%2d", t, t, t);  /*When we using %3d or %2d for integer of length 4 it prints
                                    that integer in first 4 cells*/
}

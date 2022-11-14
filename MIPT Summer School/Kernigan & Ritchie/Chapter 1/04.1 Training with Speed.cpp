#include <stdio.h>
main()
{
    float S, v;
    int t, t0, t1, step;

    v = 10.5;
    t0 = 0;
    t1 = 15;
    step = 1;

    printf("time:  distance:\n");

    t = t0;
    while (t <= t1)
    {
        S = 3.6 * (v * t);
        printf ("%3d%10.1f\n", t, S);
        t = t + step;
    }
}

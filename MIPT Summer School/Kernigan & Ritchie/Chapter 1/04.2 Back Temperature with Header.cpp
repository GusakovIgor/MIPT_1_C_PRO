#include <stdio.h>
main()
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 150;
    step = 15;

    printf("Celsius into Fahr\n");

    celsius = lower;
    while(celsius <= upper)
    {
        fahr = 32 + (9.0/5.0)*celsius;
        printf("%5.0f%9.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

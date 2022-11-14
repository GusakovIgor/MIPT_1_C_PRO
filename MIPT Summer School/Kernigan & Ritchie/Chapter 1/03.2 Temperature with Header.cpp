#include <stdio.h>
main()
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahr into Celsius\n");

    fahr = lower;
    while (fahr <= upper)
    {
        celsius = (5.0/9.0)*(fahr - 32);
        printf("%5.0f%9.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

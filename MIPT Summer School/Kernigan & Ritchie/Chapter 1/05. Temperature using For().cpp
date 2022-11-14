#include <stdio.h>
main()
{
    int fahr;

    printf("Fahr into Celsius\n");

    for (fahr = 300; fahr >= 0; fahr = fahr - 20)
        printf("%4d  -- %6.1f\n", fahr, (fahr - 32)*(5.0/9.0));
}

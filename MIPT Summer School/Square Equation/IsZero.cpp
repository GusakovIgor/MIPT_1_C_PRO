#include "SquareEquation.h"
#define NUM_TESTS_ZERO 2    // Number of tests for SquareEqSolver function

int IsZero (double value)
    {
    return (fabs(value) <= 0.00001);
    }

void IsZero_test ()
    {
    double value[] = {0.333333 - 0.3333333, 5.64575 - 4.645751};
    double exp[]   = {1, 0};
    double res = 0;
    int number = 0;

    for (number = 0; number < NUM_TESTS_ZERO; number++)
        {
        res = IsZero(value[number]);
        if (res == exp[number])
            printf("\n Test %d passed", number);
        else
            {
            printf("\n Test %d failed\n", number);
            printf("---expected %lg but recieved %lg\n", exp[number], res);
            }
        }
    }

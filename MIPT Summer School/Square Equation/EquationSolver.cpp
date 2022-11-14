#include "SquareEquation.h"
#define NUM_TESTS 6         // Number of tests for SquareEqSolver function

int SquareEqSolver (double a, double b, double c, double *x1, double *x2)
    {
        assert (x1 != NULL);                // Checks
        assert (x2 != NULL);
        assert (x1 != x2);

    double D = b*b - 4*a*c;                 // Counting Discriminant

    if (a == 0)                             // Checking case when equation is not square at all (a = 0)
        if (b == 0)
            return (c == 0)? INF : 0;       // If all coeffs are 0, any number will be root,
        else                                // so we return special constant INF (infinity)
            {
            *x1 = -c/b;
            *x2 = 0;
            return 1;
            }

    else if (D < 0)                         // If equation is square (a != 0), counting roots
        {                                   // and returning number of them, depending on discriminant
        *x1 = 0;
        *x2 = 0;
        return 0;
        }
    else if (D == 0)
        {
        *x1 = -b/(2*a);
        *x2 = 0;
        return 1;
        }
    else if (D > 0)
        {
        *x1 = (-b + sqrt(D))/(2*a);
        *x2 = (-b - sqrt(D))/(2*a);
        return 2;
        }

    }

void SquareEqSolver_Test ()
    {
        //  Boundary Cases:
        //      à = 0, b  = 0 - depending on c there is infinite number of roots, or 0
        //             b != 0 - always only 1 solution x = -c/b
        //
        //      a != 0: D > 0 - always 2 roots
        //              D = 0 - 1 root
        //              D < 0 - 0 roots

    double r1 = 0,
           r2 = 0,
          res = 0;

    double a[] = { 0, 0,  0, -1, 1, 1},
           b[] = { 0, 0,  3,  4, 4, 2},
           c[] = {-1, 0, -1,  3, 4, 2};

    double  exp[] = {0, INF, 1, 2, 1, 0},
            exp_root1[] = {0, 0, 0.333333, -0.645751, -2, 0},
            exp_root2[] = {0, 0, 0       ,  4.64575 ,  0, 0};

    int number = 0;

    for (number = 0; number < NUM_TESTS; number++)
        {
        res = SquareEqSolver (a[number], b[number], c[number], &r1, &r2);
        if (res == exp[number] && IsZero(r1 - exp_root1[number]) == 1 && IsZero(r2 - exp_root2[number]) == 1)
            printf("\n Test %d passed", number+1);
        else
            {
            printf("\n Test %d failed\n", number+1);
            printf("---expected NumRoots  %lg, but recieved %lg\n", exp[number], res);
            printf("---expected 1-st Root %lg, but recieved %lg\n", exp_root1[number], r1);
            printf("---expected 2-nd Root %lg, but recieved %lg\n", exp_root2[number], r2);
            }
        }
    }

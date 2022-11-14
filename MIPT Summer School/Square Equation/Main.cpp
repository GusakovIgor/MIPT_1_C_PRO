#include "SquareEquation.h"

int main()
    {
    double a = 0,                                           // Coefficients
           b = 0,
           c = 0;

    printf("#Square Equation Solver\n");                    // Introducing program
    printf("#By Gusakov Igor, 30.08.2020\n");

    printf("\n#Testing SquareEqSolver:");                   // Unit-testing
    SquareEqSolver_Test ();
    printf("\n");

    printf("\n#Testing IsZero:");
    IsZero_test ();
    printf("\n\n");

    EquationMaker (&a, &b, &c);                             // Printing equation

    double x1 = 0, x2 = 0;                                  // Roots
    int NumRoots = SquareEqSolver (a, b, c, &x1, &x2);      // Getting number of roots for our equation

    switch (NumRoots)                                       // Depending on NumRoots choosing
        {                                                   // how to output an answer
        case 0:   printf("#And it has no roots :(");
                  break;
        case 1:   printf("#And it has one root: %g", x1);
                  break;
        case 2:   printf("#And it has two roots: %g and %g", x1, x2);
                  break;
        case INF: printf("#And any number is a root!");
                  break;
        default:  printf("#Oops...\nmain(): Error - NumRoots = %d", NumRoots);
        }

    return 0;
    }

#include "SquareEquation.h"

//---------------------------------------------------------------------------------------
//! Equation Maker Function:
//!
//! @param [out]  a  coefficient at x^2
//! @param [out]  b  coefficient at x^1
//! @param [out]  c  coefficient at x^0
//!
//! @return None
//!
//! @description: This function works with user and print square equation:
//!               1.Work with user
//!               2.Step by step printing equation using recieved coeffs
//!               3.Consider special case (all coeffs - 0) and print ending of equation
//---------------------------------------------------------------------------------------

void EquationMaker (double *a, double *b, double *c)
    {
    assert (a != NULL);                             // Checking
    assert (b != NULL);
    assert (c != NULL);
    assert (a != b);
    assert (b != c);
    assert (c != a);

    printf("#Please enter coefficients:\n");
    printf("a = "); scanf("%lg", a);
    printf("b = "); scanf("%lg", b);
    printf("c = "); scanf("%lg", c);

    printf("\n#Your equation is: ");

    if (*a < 0)                                     // Working with a higher coeff. (put the correct sign and
        printf("-");                                //                               write down formula in correct form)
    if (fabs(*a) == 1)
        printf("x^2 + ");
    else if (*a != 0)
        printf("%lgx^2 + ", fabs(*a));


    if (*b < 0)                                     // Just like with higher coeff. but prepearing for cases when
        (*a == 0)? printf("-"): printf("\b\b- ");   // a = 0, and b < 0 or a != 0 and b < 0
    if (fabs(*b) == 1)
        printf("x + ");
    else if (*b != 0)
        printf("%lgx + ", fabs(*b));

    if (*c < 0)                                     // Totally like with coeff. b
        (*b == 0)? printf("-"): printf("\b\b- ");
    if (fabs(*c) == 1)
        printf("1");
    else if (*c != 0)
        printf("%lg", fabs(*c));
    else
        printf("\b\b\b");

    if (*a == 0 && *b == 0 && *c == 0)              // For case, when all coeffs are 0
        printf("0");                                // (for we can see "0 = 0", not " = 0")

    printf(" = 0\n\n");
    }

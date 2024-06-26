#include <stdio.h>
#include <math.h>
#include <assert.h>

#define INF -1
#define NUM_TESTS 6         // Number of tests for SquareEqSolver function
#define NUM_TESTS_ZERO 2    //                     IsZero function

int  SquareEqSolver (double a, double b, double c, double* x1, double* x2);
void EquationMaker  (double *a, double *b, double *c);
void SquareEqSolver_Test ();
int  IsZero (double value);
void IsZero_test ();

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

    EquationMaker(&a, &b, &c);                              // Printing equation

    double x1 = 0, x2 = 0;                                  // Roots
    int NumRoots = SquareEqSolver(a, b, c, &x1, &x2);       // Getting number of roots for our equation

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
    if (abs(*a) == 1)
        printf("x^2 + ");
    else if (*a != 0)
        printf("%dx^2 + ", abs(*a));


    if (*b < 0)                                     // Just like with higher coeff. but prepearing for cases when
        (*a == 0)? printf("-"): printf("\b\b- ");   // a = 0, and b < 0 or a != 0 and b < 0
    if (abs(*b) == 1)
        printf("x + ");
    else if (*b != 0)
        printf("%dx + ", abs(*b));

    if (*c < 0)                                     // Totally like with coeff. b
        (*b == 0)? printf("-"): printf("\b\b- ");
    if (abs(*c) == 1)
        printf("1");
    else if (*c != 0)
        printf("%d", abs(*c));
    else
        printf("\b\b\b");

    if (*a == 0 && *b == 0 && *c == 0)              // For case, when all coeffs are 0
        printf("0");                                // (for we can see "0 = 0", not " = 0")

    printf(" = 0\n\n");
    }


//---------------------------------------------------------------------------------------
//! Square Equation Solver Function:
//!
//! @param [in]  a  coefficient at x^2
//! @param [in]  b  coefficient at x^1
//! @param [in]  c  coefficient at x^0
//! @param [out] x1 pointer on 1-st root
//! @param [out] x2 pointer on 2-nd root
//!
//! @return Number of roots for our equation (int)
//!
//! @description: This function solving equation:
//!               1.Finding an answer for special case (when first coeff. a is 0)
//!               2.Finding an answer for all other cases (dependig on discriminant)
//---------------------------------------------------------------------------------------

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
        //      � = 0, b  = 0 - depending on c there is infinite number of roots, or 0
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

#include <stdio.h>
#include <assert.h>
#include <math.h>

#define INF -1

void EquationMaker (double *a, double *b, double *c);

int  SquareEqSolver (double a, double b, double c, double *x1, double *x2);
void SquareEqSolver_Test ();

int  IsZero (double value);
void IsZero_test ();

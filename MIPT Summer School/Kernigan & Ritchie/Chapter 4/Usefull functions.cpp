#include <stdio.h>

int isspace (char symbol)
    {
    if (symbol == ' ' || symbol == '\t')
        return 1;
    else
        return 0;
    }

int isdigit (char symbol)
    {
    if ('0' <= symbol && symbol <= '9')
        return 1;
    else
        return 0;
    }

#define MAXVAL 100      /* максимальна€ глубина стека */
int sp = 0;             /* следующа€ свободна€ позици€ в стеке */
double val [MAXVAL];   /* стек */

/* push: положить значение f в стек */
void push(double f)
    {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf( "ошибка: стек полон, %g не помещаетс€\n", f);
    }

/* pop: вз€ть с вершины стека и выдать в качестве результата */
double pop(void)
    {
    if (sp > 0)
        return val[--sp];
    else {
        printf( "ошибка: стек пуст\n");
        return 0.0;
        }
    }

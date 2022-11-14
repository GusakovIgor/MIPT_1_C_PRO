#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

//---------------------------------------------------------
//! Calculating Arithmetic progression function:
//!
//! @param [in] trside - length of the triangle side
//!
//!
//! @return int - size of array where we need to store our triangle
//!
//! @description: This function simply calculating, using formula of arithmetic progression
//---------------------------------------------------------
int ArProgrCalc (int trside);

//---------------------------------------------------------
//! Getting an element function:
//!
//! @param [in] trarr  - pointer on array of elemnts which our "triangle" containig
//! @param [in] line   - line in "triangle", from which we want to take an element (line < trside)
//! @param [in] column - column in "triangle", from which we want to take an element (column < line)
//!
//!
//! @return int* - pointer on an element we want to get from "triangle"
//!
//! @description: This function calculating adress in memory on element we need:
//!               1) It gets to the right line, using ArProgrCalc(line)
//!               2) It gets to the right element in line, using column
//---------------------------------------------------------
int* ElemGetter (int* trarr, size_t line, size_t column);

//---------------------------------------------------------
//! Printing "triangle" array function:
//!
//! @param [in] trarr - pointer on array of elemnts which our "triangle" containig
//! @param [in] size  - size of array where we need to store our triangle
//!
//!
//! @return int* - pointer on an element we want to get from "triangle"
//!
//! @description: This function calculating adress in memory on element we need:
//!               1) It gets to the right line, using ArProgrCalc(line)
//!               2) It gets to the right element in line, using column
//---------------------------------------------------------
void PrintArr (int* trarr, int size);

int main()
    {

    int trside = 0;
    printf("Plese, enter side of triangle:\nSize = ");
    scanf("%d", &trside);

    int size = ArProgrCalc (trside);

    int* text = (int*) calloc (size, sizeof(int));
    for (int i = 0; i < size; i++)
        text[i] = i;

    size_t line = 0, column = 0;
    printf("\nPlease enter position of element you need (line and column):\n");
    printf("line = ");      scanf ("%d", &line);
    printf("column = ");    scanf ("%d", &column);

    assert (column <= line);
    assert (line <  trside);

    int* elem = ElemGetter (text, line, column);
    printf("Your element is %d", *elem);

    printf("\n\nYour triangle array is:\n");
    PrintArr (text, size);

    free(text);

    return 0;
    }

int ArProgrCalc (int trside)
    {
    int size = trside * (trside + 1) / 2;
    return size;
    }

int* ElemGetter (int* trarr, size_t line, size_t column)
    {
    int* adr = trarr + ArProgrCalc(line) + column;
    return adr;
    }

void PrintArr (int* trarr, int size)
    {
    int line = 1;
    for (int i = 0; i < size; i++)
        if (i+1 == ArProgrCalc (line))
            {
            printf("%d\n", trarr[i]);
            line++;
            }
        else
            if (trarr[i] < 10)
                printf("%d   ", trarr[i]);
            else if (trarr[i] < 100)
                printf("%d  ", trarr[i]);
            else
                printf("%d ", trarr[i]);
    }

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

#define MAXVAL 100      /* ������������ ������� ����� */
int sp = 0;             /* ��������� ��������� ������� � ����� */
double val [MAXVAL];   /* ���� */

/* push: �������� �������� f � ���� */
void push(double f)
    {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf( "������: ���� �����, %g �� ����������\n", f);
    }

/* pop: ����� � ������� ����� � ������ � �������� ���������� */
double pop(void)
    {
    if (sp > 0)
        return val[--sp];
    else {
        printf( "������: ���� ����\n");
        return 0.0;
        }
    }

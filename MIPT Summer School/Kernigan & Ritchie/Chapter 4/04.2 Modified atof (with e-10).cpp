#include <stdio.h>
#include <assert.h>
#include "Usefull functions.cpp"
double atof (char s[]);

int inum_get (char s[], int *i);

int main()
    {
    char number[] = "-105.5e";
    double dnumber = atof(number);
    printf("%lg", dnumber);

    return 0;
    }

double atof (char s[])
    {
    double val = -1;
    int i, power = 1, sign = 1, exsign = 1;

    for (i = 0; isspace(s[i]); i++)    // Пропускаем символы разделители
        ;

    sign = (s[i] == '-')? -1 : 1;       // Записываем знак и переходим к числу
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++) // Считываем целое число
        val = 10*val + (s[i] - '0');             // Считываем число

    if (s[i] == '.')                    // Считываем дробную часть (записанную с помощью точки)
        i++;
    for (power = 1; isdigit(s[i]); i++)
        {
        val = 10*val + (s[i] - '0');
        power *= 10;
        }


    if (s[i] == 'e')                    // Считываем экспоненту и её знак (если они есть)
        i++;
    exsign = (s[i] == '-')? -1: 1;
    if (s[i] == '-' || s[i] == '+')
        i++;

    int expower;
    for (expower = 0; isdigit(s[i]); i++) // Считываем целое число
        expower = 10*expower + (s[i] - '0');

    for (int t = 0; t < expower; t++) // Увеличиваем или уменьшаем уже известную степень
        if (exsign == -1)
            power *= 10;
        else
            power /= 10;

    return sign * val / power;
    }


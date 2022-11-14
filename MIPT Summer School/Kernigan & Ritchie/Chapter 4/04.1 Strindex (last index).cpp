#include <stdio.h>

int strindex(char s[], char t[]);

int main()
    {
    char s[] = "Mama mila ramu";
    char t[] = "ma";
    printf("%d", strindex(s, t));

    return 0;
    }

int strindex(char s[], char t[])
    {
    int i = 0, j = 0, k = 0, ind = -1;

    for (i = 0; s[i] != '\0'; i++)
        {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            ind = i;
        }

    return ind;
    }

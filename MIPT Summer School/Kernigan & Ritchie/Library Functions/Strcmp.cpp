#include <stdio.h>
#include <locale.h>

int Strcmp (const unsigned char *str1, const unsigned char *str2);

int main()
    {
    setlocale (LC_ALL, "Russian");

    unsigned char str1[] = "On the Highway to hell";
    unsigned char str2[] = "On the Highway home";

    int a = Strcmp (str1, str2);
    printf("%d", a);
    getchar();
    return 0;
    }

//---------------------------------------------------------------------------------------
//! String compare function:
//!
//! @param [out]  str1  1-st string to compare
//! @param [out]  str2  2-nd string to compare
//!
//! @return integer
//!
//! @description: This function compares two strings:
//!               1.Checking if str1[i] = str2[i] while it's true
//!               2.Giving help print (ASCII codes of first not equal symbols - neq_symbol 1 and 2)
//!               3.Depending on those elements returns integer nuber which means that str1 > str2 or str1 < str2 or they equals
//---------------------------------------------------------------------------------------

int Strcmp (const unsigned char *str1, const unsigned char *str2)
    {
    int i = 0;                                                      // Iterationally checking if str1[i] = str2[i]
    for (i = 0; *(str1 + i) != '\0' && *(str2 + i) != '\0' && *(str1 + i) == *(str2 + i); i++)
        ;
    int neq_symbal1 = *(str1 + i);
    int neq_symbal2 = *(str2 + i);

    if (neq_symbal1 != '\0' && neq_symbal2 != '\0')                 // Help print with ASCII codes
        printf("ASCII code of %c - %d, of %c - %d\n", neq_symbal1, neq_symbal1, neq_symbal2, neq_symbal2);

    if (neq_symbal1 == neq_symbal2)                 //  0 if strings are equal
        return 0;
    else if (neq_symbal1 > neq_symbal2)             //  1 if str1 > str2
        return 1;
    else if (neq_symbal1 < neq_symbal2)             // -1 if str1 < str2
        return -1;
    }

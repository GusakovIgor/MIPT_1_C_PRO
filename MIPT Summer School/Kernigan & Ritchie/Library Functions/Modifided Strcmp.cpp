#include "Onegin_Functions.h"

int Strcmp (unsigned char *str1, unsigned char *str2);

int isspace (char c);

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

int Strcmp (unsigned char *str1, unsigned char *str2)
    {
    int i = 0;                                                      // Iterationally checking if str1[i] = str2[i]
    int j = 0;
    for (i, j; *(str1 + i) != '\0' && *(str2 + j) != '\0' &&
                                            (*(str1 + i) == *(str2 + j) || isspace(*(str1 + i)) || isspace(*(str2 + j)));)
        {
        if (isspace(*(str1 + i)))
            i++;
        if (isspace(*(str2 + j)))
            j++;
        if (*(str1 + i) == *(str2 + j))
            {
            i++;
            j++;
            }
        }

    int neq_symbal1 = *(str1 + i);
    int neq_symbal2 = *(str2 + j);

    if (neq_symbal1 != '\0' && neq_symbal2 != '\0')                 // Help print with ASCII codes
        printf("ASCII code of %c - %d, of %c - %d\n", neq_symbal1, neq_symbal1, neq_symbal2, neq_symbal2);

    if (neq_symbal1 == neq_symbal2)                 //  0 if strings are equal
        return 0;
    else if (neq_symbal1 > neq_symbal2)             //  1 if str1 > str2
        return 1;
    else if (neq_symbal1 < neq_symbal2)             // -1 if str1 < str2
        return -1;
    }

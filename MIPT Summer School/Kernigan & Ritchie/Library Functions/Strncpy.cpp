#include <stdio.h>

char *Strncpy (char* LineCopyTo, const char* LineCopyFrom, int number);

int main()
    {
    int n = 0;
    printf ("Please, enter nuber of symbols you want to be copied:\n");
    printf ("n = ");    scanf ("d", &n);

    char LineCopyTo[] = "Let's copy next phrase here'";
    const char LineCopyFrom[] = "ereh esarhp txen ypoc s'teL";

    char* point = Strncpy (LineCopyTo, LineCopyFrom, n);
    printf("%s", point);

    return 0;
    }

//---------------------------------------------------------------------------------------
//! String'n'copy function (:
//!
//! @param [out]  LineCopyTo     Pointer on line,  in  which we need to copy something
//! @param [out]  LineCopyFrom   Pointer on line, from which we need to copy something
//! @param [in]   number         Number of elements, that we need to copy
//!
//!
//! @return char* LineCopyTo     Pointer on final line
//!
//! @description: This function :
//!               1. Working with strings:
//!                     a) While we're in both lines || in line we're going copy to and out of line we going to copy from
//!                     b) In first case we assign value of current variable in LineCopyFrom for current variable in LineCopyTo
//!                     c) In second case we assign '\0' for every variable in LineCopyTo while we don't have copied nuber symbols
//---------------------------------------------------------------------------------------

    char *Strncpy (char* LineCopyTo, const char* LineCopyFrom, int number)
        {
        int In_ToStr = 1,
            In_FromStr = 1;
        for (int i = 0; (In_ToStr == 1 || i < number) && i < number && In_FromStr == 1; i++)
            {
            if (In_FromStr != 0)
                LineCopyTo[i] = LineCopyFrom[i];
            else
                LineCopyTo[i] = '\0';

            if (LineCopyTo[i] == '\0')
                In_ToStr = 0;
            if (LineCopyFrom[i] == '\0')
                In_FromStr = 0;
            }

        return LineCopyTo;
        }

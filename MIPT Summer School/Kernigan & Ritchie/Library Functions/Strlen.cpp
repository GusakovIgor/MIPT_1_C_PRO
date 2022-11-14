#include <stdio.h>

int strlen (const char *cs);
void strlen_test (void);

int main ()
    {
    strlen_test();
    return 0;
    }

//--------------------------------------------------------------------
//! String length finder
//!
//! @param [out]  *cs pointer on 0 element of string
//!
//! @return count - String length
//!
//! @descriotion: This function simply counting symbols in string while there is no '\0'
//--------------------------------------------------------------------

int strlen (const char *cs)
    {
    int count = 0;
    for (int i = 0; cs[i] != '\0'; i++)
        count++;
    return count;
    }

void strlen_test (void)
    {
    char tstring[1000] = "ababa";
    int len = 0;

    for (int i = 1; i <= 10; i++)
        {
        tstring[3 + i*2] = 'b';
        tstring[4 + i*2] = 'a';

        if ((len = strlen(tstring)) == 5 + i*2)
            printf ("Test %d passed!\t", i);
        else
            printf ("Test %d failed!\n      \
                     Expected len is %d but recieved - %d\t", i, 5 + i*2, len);

        printf ("Your string is: ");
        for (int t = 0; t < len; t++)
            putchar(tstring[t]);
        printf("\n\n");
        }
    }

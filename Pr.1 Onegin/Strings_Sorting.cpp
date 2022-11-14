
//---------------------------------------------------------------------------------------
//! MyQuickSort function: sorting an array of strings
//!     1) Checking if array is sorted
//!     2) Checking if we need to sort only two elements
//!     3) Put the middle string (MS) in the beginning of array and compare each other string with it
//!         a) increase last (which responsible for border of elements who < MS and not checked (or checked, but >= MS))
//!         b) if string < MS => change it with the first element after others, which we already know they're < MS
//!     4) After checking all strings, change MS with the last element, which < MS
//!     5) Great! We have an array, where one part < MS, other one >= MS
//!     6) So we can recusively sort these parts and get fully sorted array in the end
//!
//! Optimisations:
//!     1) Three parted array (> p, == p, < p)
//!     2) At great depth of recursion, when small arrays we can call another (not recursion) sort. The best is InsertSort
//!     3) Strategy of choosing p (pivot)
//!         a) fixed (фиксированное) plfce in array
//!         b) random
//!         c) Medianofmedians
//!         d) Median
//!
//! @param [out] sarray     - pointer on the beginig of array with structures
//! @param [in]  left       - left  border of sorting
//! @param [in]  right      - right border of sorting
//! @param [out] comparator - function, that compares two strings
//!
//! @return integer (0)
//!
//---------------------------------------------------------------------------------------
int MyQuickSort (int* sarray, int left, int right)
{

    if (right - left <= 0)
        return 0;
    if (right - left == 1)
        {
        if (sarray[left] > sarray[right])
            swap(sarray[left], sarray[right]);
        return 0;
        }


    swap( (sarray + left), (sarray + (left+right)/2) );

    int last = left;
    for (int i = left + 1; i <= right; i++)
        {
        if (Comp (sarray + left, sarray + i) > 0)
            {
            last++;
            Swap ((sarray + last), (sarray + i));
            }
        }

    Swap( (sarray + left), (sarray + last) );


    if (right - left <= 0)
        return 0;
    if (right - left == 1)
        {
        if (Comp (sarray + left, sarray + right) > 0)
            Swap ( (sarray + left),  (sarray + right));
        return 0;
        }

    MyQuickSort (sarray, left,     last,  Comp);
    MyQuickSort (sarray, last + 1, right, Comp);

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
int Forward_Strcmp_rus (char *str1, char *str2)
    {
    assert(str1 != 0);
    assert(str2 != 0);

    int i = 0;
    int j = 0;
    for (i, j; *(str1 + i) != '\0' && *(str2 + j) != '\0' &&
                                        (*(str1 + i) == *(str2 + j) || isspace(*(str1 + i)) || isspace(*(str2 + j))); )
        {
        if (!isspace(*(str1 + i)) && !isspace(*(str2 + j)) && *(str1 + i) == *(str2 + j))
            {
            i++;
            j++;
            }
        if (isspace(*(str1 + i)))
            i++;
        if (isspace(*(str2 + j)))
            j++;
        }

    int neq_symbal1 = *(str1 + i);
    int neq_symbal2 = *(str2 + j);

    if (neq_symbal1 != '\0' && neq_symbal2 != '\0')     // Help print with ASCII codes
        printf("ASCII code of %c - %d, of %c - %d\n", neq_symbal1, neq_symbal1, neq_symbal2, neq_symbal2);

    if (neq_symbal1 == neq_symbal2)                     //  0 if strings are equal
        return 0;
    else if (neq_symbal1 < neq_symbal2)                 //  1 if str1 > str2
        return 1;
    else if (neq_symbal1 > neq_symbal2)                 // -1 if str1 < str2
        return -1;
    }

int isspace (char c)
    {
    if (c == ',' || c == '.' || c == '?' || c == ':' || c == ';' || c == '\"' || c == '\'' || c == '!' || c == '-')
        return 1;
    else
        return 0;
    }

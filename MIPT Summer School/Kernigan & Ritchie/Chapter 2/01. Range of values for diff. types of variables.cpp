#include <stdio.h>
#include <limits.h>
#include <math.h>

main(){
    int Value = 0;
    int min = 0;
    int max = 0;
    printf("\t    Range of values for different types of variables\n");
    printf("  Using standard headers: \t\t\t\t Calculating:\n\n");

    Value = 8*sizeof(unsigned char);
    min = 0;
    max = pow(2, Value) - 1;
    printf("unsigned char: from %d to %d \t\t\t\t from %d to %d\n", 0, UCHAR_MAX, min, max);
    Value = 8*sizeof(signed char);
    min = -pow(2, Value)/2;
    max = pow(2, Value)/2-1;
    printf("signed char: from %d to %d \t\t\t\t from %d to %d\n\n", SCHAR_MIN, SCHAR_MAX, min, max);

    Value = 8*sizeof(unsigned short);
    min = 0;
    max = pow(2, Value) - 1;
    printf("unsigned short: from %d to %d \t\t\t from %d to %d\n", 0, USHRT_MAX, min, max);
    Value = 8*sizeof(signed short);
    min = -pow(2, Value)/2;
    max = pow(2, Value)/2-1;
    printf("signed short: from %d to %d \t\t\t from %d to %d\n\n", SHRT_MIN, SHRT_MAX, min, max);

    Value = 8*sizeof(unsigned int);
    min = 0;
    max = pow(2, Value) - 1;
    printf("unsigned int: from %d to %d \t\t\t\t from %d to %d\n", 0, UINT_MAX, min, max);
    Value = 8*sizeof(signed int);
    min = -pow(2, Value)/2;
    max = pow(2, Value)/2-1;
    printf("signed int: from %d to %d \t\t from %d to %d\n\n", INT_MIN, INT_MAX, min, max);

    Value = 8*sizeof(unsigned long);
    min = 0;
    max = pow(2, Value) - 1;
    printf("unsigned long: from %d to %d \t\t\t\t from %d to %d\n", 0, ULONG_MAX, min, max);
    Value = 8*sizeof(unsigned long);
    min = -pow(2, Value)/2;
    max = pow(2, Value)/2-1;
    printf("signed long: from %d to %d \t\t from %d to %d\n\n", LONG_MIN, LONG_MAX, min, max);

    return 0;
}

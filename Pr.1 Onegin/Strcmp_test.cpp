#include "Strings_Sorting.cpp"

int main()
    {

    setlocale(LC_ALL, "Russian");

    char* a = "וובגדה";
    char* b = "וו";

    struct str_info str1;
    struct str_info str2;

    str1.ptr = a;
    str2.ptr = b;
    str1.size = strlen(a);
    str2.size = strlen(b);

    printf("%d\n", Forward_Strcmp_rus(str1, str2) );
    printf("%d\n", strcmp(a, b));
    for (int c = 'ְ'; c >= 'ְ' && c <= 'ÿ'; c++)
        printf("%c - %d\n", c, c);
    return 0;
    }

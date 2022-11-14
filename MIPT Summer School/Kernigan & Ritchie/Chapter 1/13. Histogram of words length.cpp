#include <stdio.h>
#define IN 1
#define OUT 0
main()
{
    int c, stay, wcount, length, white;
    stay = OUT;
    wcount = length = 0;

    while ((c = getchar()) != '*'){
        white = (c != ' ' || c != '\t' || c);
        if (stay == OUT && c != ' '){
            wcount++;
            stay = IN;
        }
        if (stay == IN && c == ' ')
            stay = OUT;
        if (stay == IN)
            length++;
    }
    printf("%d length: %d", wcount, length);
}

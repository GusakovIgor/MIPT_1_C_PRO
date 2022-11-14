#include <stdio.h>
#define MAXLINE 10

int getline(char line[], int lim);
//void copy(char to[], char from[]);

main(){

    int i, c;
    int len;
    int max;
    char line [MAXLINE];
    char longest [MAXLINE];
    char reserve [MAXLINE];
    max = 0;

    while ((len = getline(line, MAXLINE)) > 0){
        if (len == MAXLINE){
            char line [2*MAXLINE];
            for (i = len; i < 2*len && (c = getchar()) != '*'; i++){
                line[i] = c;
                len++;
            }
        }

        /*else if (len > max){
            max = len;
            copy(longest, line);
        }*/
    }
    for (i = 0; i < 2*MAXLINE; i++)
        printf("%c", line[i]);
    printf("0");
    return 0;
}



int getline (char s[], int lim){
    int c, i;
    for (i = 0; i < lim && (c = getchar()) != '*' && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    if (i != lim)
        s[i] = '\0';
    return i;
}

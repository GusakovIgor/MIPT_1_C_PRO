#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

int htol(char s[]){
    int num;
    int len = strlen(s);            /* Находим длину строки*/
    printf("%d", len);
    for (int i = 2; i < len; i++){

    }
    return num;
}

int main(){
    char s[MAX];    /* Массив длины 10 (2 символа для 0x и 8 - для шестнадцетиричного числа) */
    int c;

    s[0] = '0';     /* Ввод массива символов */
    s[1] = 'x';
    for (int i = 2; i < MAX && (c = getchar()) != '\n'; i++){
        s[i] = tolower(c);
    }
    /*int t = htol(s);*/
    printf("%s", s);
    return 0;
}

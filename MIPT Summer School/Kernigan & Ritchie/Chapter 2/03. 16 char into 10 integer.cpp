#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

int htol(char s[]){
    int num;
    int len = strlen(s);            /* ������� ����� ������*/
    printf("%d", len);
    for (int i = 2; i < len; i++){

    }
    return num;
}

int main(){
    char s[MAX];    /* ������ ����� 10 (2 ������� ��� 0x � 8 - ��� ������������������ �����) */
    int c;

    s[0] = '0';     /* ���� ������� �������� */
    s[1] = 'x';
    for (int i = 2; i < MAX && (c = getchar()) != '\n'; i++){
        s[i] = tolower(c);
    }
    /*int t = htol(s);*/
    printf("%s", s);
    return 0;
}

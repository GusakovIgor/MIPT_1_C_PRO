#include <stdio.h>
#include <string.h>
#define MAX 10

void squeeze (char s1[], char s2[]){
    int i, j;
    int len2 = strlen(s2);
    bool same = false;

    for (i = j = 0; s1[i] != '\0'; i++){
        for (int t = 0; t < len2; t++){
            if (s1[i] == s2[t])
                same = true;
        }
        if (same == false)
            s1[j++] = s1[i];
        same = false;
    }
    printf("%s", s1);
}

int main(){
    char s1[MAX];
    char s2[MAX];
    int c;

    for (int i = 0; i < MAX && (c = getchar()) != '\n'; i++)
        s1[i] = c;
    for (int i = 0; i < MAX && (c = getchar()) != '\n'; i++)
        s2[i] = c;

    return 0;
}

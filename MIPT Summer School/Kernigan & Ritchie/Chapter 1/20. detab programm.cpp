#include <stdio.h>
#define N 8 //Шаг нашей табуляции в пробелах (В компьютере табуляция = 8 пробелам)

int k = 0;
int place = 0;

void TabsReplacer(){    //Заменяет табуляцию на пробелы
    extern int place, k;
    while (place >= k*N)    //Находим до какого "стопа" табуляции нужно дойти пробелами
        k++;
    for (place; place < k*N; place++)   //Доходим до этого стопа, автоматически изменяя place
        putchar(' ');
}

main(){
    int c;
    while ((c = getchar()) != '0')
        if (c == '\t')
            TabsReplacer ();
        else{
            putchar(c);
            place++;
        }

    return 0;
}

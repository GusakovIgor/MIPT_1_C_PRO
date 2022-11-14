#include <stdio.h>
#define LIMIT 20    //Ограничение по длине строки
#define N 8     //Шаг нашей табуляции в пробелах

int line[LIMIT];

int LineProcessing(){
    int LastSepNumber = -1;
    for (int i = 0; line[i] != EOF && i < LIMIT; i++){      //Считываем строку
        line[i] = getchar();
        if (line[i] == ' ' && i < LIMIT)
            LastSepNumber = i;              //И находим последний разделитель, который заканчивается раньше границы
        if (line[i] == EOF)     //Проверка на конец файла
            LastSepNumber = i;
    }
    return LastSepNumber;
}

main(){
    int c, LastSep;

    LastSep = LineProcessing();     //Считаем первую строку и найдём в ней последний подходящим разделителем (ППР)
    while(line[LastSep] != EOF){

        if (LastSep != -1 && line[LastSep] != EOF){     //Если есть ППР выведем часть строки до ППР (включительно)
            for (int i = 0; i <= LastSep; i++)
                putchar(line[i]);
            putchar('\n');          //Потом сделаем новую строку
            for (int i = LastSep + 1; i < LIMIT; i++)
                putchar(line[i]);   //Потом выведем оставшиеся символы
        }
        else
            printf("fuck");         //Если разделителей нет, то шо поделать, у меня лапки

        LastSep = LineProcessing();
    }

    return 0;
}

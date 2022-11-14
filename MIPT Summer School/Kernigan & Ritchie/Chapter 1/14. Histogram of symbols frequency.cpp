#include <stdio.h>
main()
{
    int i, c, nwhites, nothers;         //Ввод переменных
    nwhites = nothers = 0;
    int ndigit[10];
    for (i = 0; i < 10; i++)
        ndigit[i] = 0;

    while ((c = getchar()) != '*')      //Подсчёт символов
        if (c >= '0' && c <= '9')
            ndigit[c-'0']++;
        else if (c == ' ' || c == '\n' || c == '\t')
            nwhites++;
        else
            nothers++;

    for (i = 0; i < 4; i++){            //Вывод первых 3-х строк гистограммы
        printf("%17d", i);
        for (int t = 0; t < ndigit[i]; t++)
            printf("-");
        printf("\n");
    }

    printf("   Number of %4d", i);      //Вывод 4-ой и 5-ой строк гистограммы
    for (int t = 0; t < ndigit[i]; t++) //Их нужно выводить отдельно, так как необходима визуализация
        printf("-");                    //того, что Number of digits - надкатегория для ввсех чисел
    i++;
    printf("\n    digits: %5d", i);
    for (int t = 0; t < ndigit[i]; t++)
        printf("-");
    printf("\n");
    i++;

    for (i = 6; i < 10; i++){           //Вывод оставшихся строк
        printf("%17d", i);
        for (int t = 0; t < ndigit[i]; t++)
            printf("-");
        printf("\n");
    }

    printf("Number of whites ");        //Вывоб Number of whites и Number of others
    for (int t = 0; t < nwhites; t++)
        printf("-");
    printf("\nNumber of others ");
    for (int t = 0; t < nothers; t++)
        printf("-");
}

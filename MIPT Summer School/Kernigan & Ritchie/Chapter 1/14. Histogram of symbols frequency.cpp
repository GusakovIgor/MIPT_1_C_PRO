#include <stdio.h>
main()
{
    int i, c, nwhites, nothers;         //���� ����������
    nwhites = nothers = 0;
    int ndigit[10];
    for (i = 0; i < 10; i++)
        ndigit[i] = 0;

    while ((c = getchar()) != '*')      //������� ��������
        if (c >= '0' && c <= '9')
            ndigit[c-'0']++;
        else if (c == ' ' || c == '\n' || c == '\t')
            nwhites++;
        else
            nothers++;

    for (i = 0; i < 4; i++){            //����� ������ 3-� ����� �����������
        printf("%17d", i);
        for (int t = 0; t < ndigit[i]; t++)
            printf("-");
        printf("\n");
    }

    printf("   Number of %4d", i);      //����� 4-�� � 5-�� ����� �����������
    for (int t = 0; t < ndigit[i]; t++) //�� ����� �������� ��������, ��� ��� ���������� ������������
        printf("-");                    //����, ��� Number of digits - ������������ ��� ����� �����
    i++;
    printf("\n    digits: %5d", i);
    for (int t = 0; t < ndigit[i]; t++)
        printf("-");
    printf("\n");
    i++;

    for (i = 6; i < 10; i++){           //����� ���������� �����
        printf("%17d", i);
        for (int t = 0; t < ndigit[i]; t++)
            printf("-");
        printf("\n");
    }

    printf("Number of whites ");        //����� Number of whites � Number of others
    for (int t = 0; t < nwhites; t++)
        printf("-");
    printf("\nNumber of others ");
    for (int t = 0; t < nothers; t++)
        printf("-");
}

#include <stdio.h>
#define LIMIT 20    //����������� �� ����� ������
#define N 8     //��� ����� ��������� � ��������

int line[LIMIT];

int LineProcessing(){
    int LastSepNumber = -1;
    for (int i = 0; line[i] != EOF && i < LIMIT; i++){      //��������� ������
        line[i] = getchar();
        if (line[i] == ' ' && i < LIMIT)
            LastSepNumber = i;              //� ������� ��������� �����������, ������� ������������� ������ �������
        if (line[i] == EOF)     //�������� �� ����� �����
            LastSepNumber = i;
    }
    return LastSepNumber;
}

main(){
    int c, LastSep;

    LastSep = LineProcessing();     //������� ������ ������ � ����� � ��� ��������� ���������� ������������ (���)
    while(line[LastSep] != EOF){

        if (LastSep != -1 && line[LastSep] != EOF){     //���� ���� ��� ������� ����� ������ �� ��� (������������)
            for (int i = 0; i <= LastSep; i++)
                putchar(line[i]);
            putchar('\n');          //����� ������� ����� ������
            for (int i = LastSep + 1; i < LIMIT; i++)
                putchar(line[i]);   //����� ������� ���������� �������
        }
        else
            printf("fuck");         //���� ������������ ���, �� �� ��������, � ���� �����

        LastSep = LineProcessing();
    }

    return 0;
}

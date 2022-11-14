//���������, ���������� ������� �� ������� � ��������� ���, ����� ��� ������ �� ���������
#include <stdio.h>
#define N 8     //��� ����� ��������� � ��������

int k = 0;      //����� k*N ������� ���������� "�����" ���������
int place = 0;
int In = 0;
int Out = 0;

void SpaceMaker(int count){     //�������� �������� ���������� ��������
    for (int i = 0; i < count; i++)
        putchar(' ');
}

void TabMaker(){
    k = In/N + 1;       //k - ������ "����" ��������� ����� In

    for (k; Out >= k*N; k++)    //��������� ����� In � Out ������� ���������, ������� ��������
        putchar('\t');
    if (k != In/N + 1)          //� ���� ���� ���� ��������� ���� ��������� ���������� k, �.�. �� ���� �� 1 ������
        k--;                    //��� ��������� "����" ����� Out
}

int Choosing(){
    int c;

    while ((c = getchar()) == ' ')      //������� "����� �� ����� ��������" (Out)
        place++;
    Out = place;

    TabMaker();     //��������� ����������� ��������� ����� ��������� ������ ��������
    if (Out >= k*N)
        SpaceMaker(Out - k*N);      //��������� ���������� ������� ����� ���������
    else
        SpaceMaker(Out - In + 1);   //��������� �������, ���� ��������� �� ����

    putchar(c);
    place++;
}

main(){
    int c;
    while ((c = getchar()) != '0')
        if (c == ' '){
            place++;
            In = place;     // ��������� "���� � ����� ��������"
            Choosing();     // ������, ��� ��� �������, ������� || ��������� � �������
        }
        else{
            place++;
            putchar(c);
        }

    return 0;
}

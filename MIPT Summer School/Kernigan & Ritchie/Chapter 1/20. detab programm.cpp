#include <stdio.h>
#define N 8 //��� ����� ��������� � �������� (� ���������� ��������� = 8 ��������)

int k = 0;
int place = 0;

void TabsReplacer(){    //�������� ��������� �� �������
    extern int place, k;
    while (place >= k*N)    //������� �� ������ "�����" ��������� ����� ����� ���������
        k++;
    for (place; place < k*N; place++)   //������� �� ����� �����, ������������� ������� place
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

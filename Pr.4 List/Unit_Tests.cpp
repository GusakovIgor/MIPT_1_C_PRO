#include "List.h"

void TestInsert ()
{
    List* lst = ListConstruct (MIN_CAPACITY + 5);

    int physical_index = 0;
    for (int value = 100; value < 1000; value += 100)
    {
        physical_index = InsertRandomAfter(lst, physical_index, value);
    }


    elem_t value = 0;
    for (int index = 1; index < 6; index += 2)
    {
        value = ExtractRandom (lst, index);
        printf ("value_%d = %lg\n", index, value);
    }


    /*
    physical_index = GetIndex (lst, 1);
    for (int value = -100; value > -400; value -= 100)
    {
        physical_index = InsertRandomBefore(lst, physical_index, value);
    }
    */

    LogicalLogsMaker  (lst);
    PhysicalLogsMaker (lst);

    lst = ListDestruct (lst);
}

void TestHeadTail ()
{
    List* lst = ListConstruct (MIN_CAPACITY);

    for (int i = 0; i < MIN_CAPACITY; i++)
    {
        InsertHead(lst, i);
    }

    for (int i = 0; i < 3; i++)
    {
        ExtractHead (lst);
        ExtractTail (lst);
    }

    InsertTail (lst, 1000);

    LogicalLogsMaker  (lst);
    PhysicalLogsMaker (lst);

    lst = ListDestruct (lst);
}

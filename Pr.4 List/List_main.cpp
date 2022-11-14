#include "List.h"

int main ()
{
//    LogsCleaner ();

//    TestHeadTail ();
//    TestInsert ();

    //
    List* lst = ListConstruct (MIN_CAPACITY);
    int index = 0;
    for (size_t value = 1; value < 10; value++)
    {
        index = InsertRandomAfter (lst, index, value/10.0);
    }
    int saved_index = GetIndex (lst, 5);

    index = InsertRandomBefore (lst, saved_index, -100);
    InsertRandomBefore (lst, index, -200);

    index = InsertRandomAfter (lst, saved_index, 100);
    InsertRandomAfter (lst, index, 200);

    //lst = This_Is_Not_Function_That_You_Need_Because_You_Do_Mot_Need_Sort (lst);

    LogicalLogsMaker (lst);
    PhysicalLogsMaker (lst);

    lst = ListDestruct (lst);

    return 0;
}


// LIST FUNCTIONS-----------------------------------------------------------------------------
List* ListConstruct (size_t capacity)
{

    LogsCleaner ();

    capacity++;         // Cause we indexing from 0, but use zero element as error indexing (like NULL indexing)
    if (capacity == 0)
    {
        int err = 1;
    }
    if (capacity < MIN_CAPACITY)
    {
        capacity = MIN_CAPACITY + 1;
    }

    List* lst = (List*) calloc (1, sizeof (List));

    lst->nodes = (Lst_Node*) calloc (capacity, sizeof (Lst_Node));
    assert (lst->nodes);

    lst->capacity = capacity;

    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;

    lst->size = 0;

    error_t err = ListStartFiller (lst);
    assert (!err);

    return lst;
}


List* ListDestruct (List* lst)
{
    free (lst->nodes);
    free (lst);

    return NULL;
}


error_t ListStartFiller (List* lst)
{
    for (int i = 1; i < lst->capacity; i++)
    {
        lst->nodes[i].next = (i < lst->capacity - 1) ? (i + 1) : 0;
        lst->nodes[i].prev = (i > 1                ) ? (i - 1) : 0;
    }

    assert (lst->nodes[0].data == 0);
    assert (lst->nodes[0].next == 0);
    assert (lst->nodes[0].prev == 0);

    return 0;
}


int InsertHead (List* lst, elem_t value)
{
    ListDump (lst, "InsertHead", 0);

    int index = InsertRandomAfter (lst, 0, value);

    ListDump (lst, "InsertHead", 0);

    return index;
}


int InsertTail (List* lst, elem_t value)
{
    ListDump (lst, "InsertTail", 0);

    int index = InsertRandomAfter (lst, lst->tail, value);

    ListDump (lst, "InsertTail", 0);

    return index;
}


elem_t ExtractHead (List* lst)
{
    ListDump (lst, "ExtractHead", 0);

    elem_t value = ExtractRandom (lst, lst->head);

    ListDump (lst, "ExtractHead", 0);

    return value;
}


elem_t ExtractTail (List* lst)
{
    ListDump (lst, "ExtructTail", 0);

    elem_t value = ExtractRandom (lst, lst->tail);

    ListDump (lst, "ExtructTail", 0);
}

int InsertRandomBefore (List* lst, int index, elem_t value)
{
    if (index <= 0)
        ListDump (lst, "InsertRandomBefore", WRONG_PHYSICAL_INDEX);

    return InsertRandomAfter (lst, lst->nodes[index].prev, value);
}


int InsertRandomAfter (List* lst, int index, elem_t value)
{
    //
    if (index > lst->size || index >= lst->capacity)
        ListDump (lst, "InsertRandomAfter", WRONG_LOGICAL_INDEX);
    //
    int old_free = lst->free;
    lst->free = lst->nodes[old_free].next;
    lst->nodes[lst->free].prev = 0;

    lst->nodes[old_free].prev = index;
    lst->nodes[old_free].data = value;

    if (index == 0)
    {
        lst->nodes[old_free].next = lst->head;
        lst->head = old_free;
    }
    else
    {
        lst->nodes[old_free].next = lst->nodes[index].next;
    }

    if (index != 0)
        lst->nodes [lst->nodes[old_free].prev].next  = old_free;

    if (lst->nodes[old_free].next != 0)
        lst->nodes[lst->nodes[old_free].next].prev = old_free;

    if (index == lst->tail)
    {
        lst->tail = old_free;
    }

    lst->size++;

    return old_free;
}

// Доделай изменение флага сортед
elem_t ExtractRandom (List* lst, int index)
{
    if (index != lst->head)
        lst->nodes[lst->nodes[index].prev].next = lst->nodes[index].next;
    if (index != lst->tail)
    {
        lst->nodes[lst->nodes[index].next].prev = lst->nodes[index].prev;
        lst->sorted = false;
    }

    elem_t value = lst->nodes[index].data;

    if (index == lst->head)
        lst->head = lst->nodes[index].next;
    if (index == lst->tail)
        lst->tail = lst->nodes[index].prev;

    lst->nodes[index].next = lst->free;
    lst->nodes[index].prev = 0;
    if (lst->free)
        lst->nodes[lst->free].prev = index;

    lst->free = index;

    lst->size--;

    return value;
}

int GetIndex (List* lst, int logical_index)
{
    if (lst->sorted)
        return logical_index;

    int count = 1;
    int iter  = lst->head;

    while (iter != 0)
    {
        if (count == logical_index)
            break;

        count++;
        iter = lst->nodes[iter].next;
    }

    if (iter == 0)
        ListDump (lst, "GetIndex", WRONG_LOGICAL_INDEX);

    return iter;
}


List* This_Is_Not_Function_That_You_Need_Because_You_Do_Mot_Need_Sort (List* lst)
{
    ListDump (lst, "Sort", 0);

    List* new_ptr = ListConstruct (lst->capacity);
    assert (new_ptr);

    size_t ptr = lst->head;
    size_t i   = 1;
    for (; i < lst->size-1; i++)
    {
        new_ptr->nodes[i].prev = i - 1;
        new_ptr->nodes[i].data = lst->nodes[ptr].data;

        if (i != lst->size-2)
            new_ptr->nodes[i].next  = i + 1;
        else
            new_ptr->nodes[i].next  = 0;

        ptr = lst->nodes[ptr].next;
    }

    new_ptr->free = i;
    new_ptr->nodes[i].prev = 0;
    new_ptr->size = lst->size;

    if (new_ptr->size > 0)
        new_ptr->head = 1;

    ListDestruct (lst);

    new_ptr->sorted = true;

    ListDump (new_ptr, "Sort", 0);

    return new_ptr;
}


// END OF LIST FUNCTIONS----------------------------------------------------------------------






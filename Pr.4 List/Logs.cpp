#include "List.h"

void LogsCleaner ()
{
    FILE* logs = fopen ("logs.txt", "w");
    fclose (logs);
}


error_t Verify (List* lst)
{
    if ((lst == NULL) || (lst->nodes == NULL))
    {
        return MEMORY_ERROR;
    }

    if (lst->capacity < MIN_CAPACITY)
    {
        return CAPACITY_ERROR;
    }

    if (lst->nodes[0].next != 0 || lst->nodes[0].prev != 0 || lst->nodes[0].data != 0)
    {
        return NULL_POINTER_ACCESS;
    }


    return 0;
}


void ListDump (List* lst, char* func, error_t err_code)
{
    if (!err_code)
        err_code = Verify (lst);

    if (err_code)
    {
        printf("ERROR with code %d in function \"%s\"\n", err_code, func);

        ErrorReport (lst, err_code);
    }
}


void ErrorReport (List* lst, error_t err_code)
{
    FILE* logs = NULL;

    #ifdef SUPERDEBUG
        logs = stderr;
    #else
        logs = fopen ("TextLogs.txt", "w");
    #endif

    switch (err_code)
    {
        case (MEMORY_ERROR):            fprintf (logs, "Error with list. Pointer on part of its memory is NULL, \n");
                                        fprintf (logs, "       please, check that you constructed everything correctly");
                                        break;

        case (CAPACITY_ERROR):          fprintf (logs, "Error with capacity. It's < MIN_CAPACITY, check if you changed it by yourself\n");
                                        fprintf (logs, "       or try to find error in Construction");
                                        break;

        case (NULL_POINTER_ACCESS):     fprintf (logs, "You've tried to go in a NULL pointer, check indexing");
                                        break;

        case (WRONG_LOGICAL_INDEX):     fprintf (logs, "Your logical index is too big\n");
                                        break;

        case (WRONG_PHYSICAL_INDEX):    fprintf (logs, "Your physical index <= 0\n");
                                        break;
    }

    fprintf (logs, "\n\nList:\n");
    fprintf (logs, "head = %d\n", lst->head);
    fprintf (logs, "tail = %d\n", lst->tail);
    fprintf (logs, "size = %d\n", lst->size);
    fprintf (logs, "free = %d\n\n", lst->free);

    fprintf (logs, "i:   data:   next:   prev:\n");
    for (int i = 0; i < lst->capacity; i++)
    {
        fprintf (logs, "%-7d ",  i);
        fprintf (logs, "%-7lg ", lst->nodes[i].data);
        fprintf (logs, "%-7d ",  lst->nodes[i].next);
        fprintf (logs, "%-7d ",  lst->nodes[i].prev);
        fprintf (logs, "\n");
    }

    fclose (logs);

    #ifdef SUPERDEBUG
        LogicalLogsMaker  (lst);
        PhysicalLogsMaker (lst);
    #endif

    assert (!"OK");
}


void LogicalLogsMaker (List* lst)
{
    FILE* GraphicLogs = fopen ("GraphicLogs_L.txt", "w");

    static int call = 0;

    fprintf (GraphicLogs, "digraph %d {\n", call);
    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #ED96EC\"]\n");

    int iter = lst->head;

    fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = \"#c81446\", label = \"{NULL}\"]\n",
                                                                        &lst->nodes[0]);

    if (lst->size != 0)
    {
        while (iter != 0)
        {
            fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", label = \"{%lg | {%d|%d|%d}}\"]\n",
                                                                                &lst->nodes[iter], lst->nodes[iter].data, lst->nodes[iter].prev, iter, lst->nodes[iter].next);
            if (iter != lst->head)
                fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[iter], &lst->nodes[lst->nodes[iter].prev]);
            else
                fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[0], &lst->nodes[iter]);

            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[iter], &lst->nodes[lst->nodes[iter].next]);

            iter = lst->nodes[iter].next;
        }
    }

    fprintf (GraphicLogs, "}");

    fclose (GraphicLogs);

    char* command_1 = (char*) calloc (100, sizeof(char));
    char* command_2 = (char*) calloc (100, sizeof(char));
    sprintf (command_1, "dot -Tjpeg GraphicLogs_L.txt > GraphicLogs_L%d.jpeg", call);
    sprintf (command_2, "start GraphicLogs_L%d.jpeg", call);

    system (command_1);
    system (command_2);

    free (command_1);
    free (command_2);

    call++;
}


void PhysicalLogsMaker (List* lst)
{
    FILE* GraphicLogs = fopen ("GraphicLogs_P.txt", "w");

    static int call = 0;

    fprintf (GraphicLogs, "digraph %d {\n", call);

    MakePlaces (lst, GraphicLogs);

    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #C0FFEE\"]\n");
    fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = \"#c81446\", label = \"{NULL | {%d|%d|%d}}\"]\n", &lst->nodes[0], lst->nodes[0].prev, 0, lst->nodes[0].next);

    if (lst->size > 0)
    {
        PrintBranch (lst, GraphicLogs, lst->head);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[0], &lst->nodes[lst->head]);
    }
    if (lst->size < lst->capacity - 1)
    {
        PrintBranch (lst, GraphicLogs, lst->free);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[0], &lst->nodes[lst->free]);
    }

    fprintf (GraphicLogs, "}");

    fclose (GraphicLogs);

    char* command_1 = (char*) calloc (100, sizeof(char));
    char* command_2 = (char*) calloc (100, sizeof(char));
    sprintf (command_1, "dot -Tjpeg GraphicLogs_P.txt > GraphicLogs_P%d.jpeg", call);
    sprintf (command_2, "start GraphicLogs_P%d.jpeg", call);

    system (command_1);
    system (command_2);

    free (command_1);
    free (command_2);

    call++;
}


void PrintBranch (List* lst, FILE* GraphicLogs, int start_index)
{
    int index = start_index;
    while (index != 0)
    {
        if (start_index == lst->free)
            fprintf (GraphicLogs, "{rank = same; \"%d\"; \"%p\" [fillcolor = \"#C0FFEE\", label = \"{free | {%d|%d|%d}}\"]; }\n", index,
                                                                            &lst->nodes[index], lst->nodes[index].prev, index, lst->nodes[index].next);
        else if (start_index == lst->head)
            fprintf (GraphicLogs, "{rank = same; \"%d\"; \"%p\" [fillcolor = \"#ED96EC\", label = \"{%lg | {%d|%d|%d}}\"]; }\n", index,
                                                                        &lst->nodes[index], lst->nodes[index].data, lst->nodes[index].prev, index, lst->nodes[index].next);
        else
        {
            printf ("ERROR in printing list, wrong start_index for branch (free or filled) printing");
            assert (!"OK");
        }

        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[index], &lst->nodes[lst->nodes[index].next]);
        if (index != lst->free && index != lst->head)
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[index], &lst->nodes[lst->nodes[index].prev]);

        index = lst->nodes[index].next;
    }
}

void MakePlaces (List* lst, FILE* GraphicLogs)
{
    fprintf (GraphicLogs, "{\n");
    fprintf (GraphicLogs, "node [shape = \"record\", color = black, fillcolor = black, label = \"1\"]\n");
    fprintf (GraphicLogs, "edge [color = white]\n");
    for (int i = 1; i < lst->capacity - 1; i++)                 // Capacity is 1 above max index of usable node
    {
        fprintf (GraphicLogs, "\"%d\" -> ", i);
    }
    fprintf (GraphicLogs, "\"%d\";\n", lst->capacity - 1);
    fprintf (GraphicLogs, "}\n");
}



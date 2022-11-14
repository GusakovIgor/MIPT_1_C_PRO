#include "Diff.h"

// Errors Processing
void SyntaxRequire (string* str, char request)
{
    if (str->pointer[str->offset++] != request)
        ErrorReport (str, WRONG_SYMBOL);
}

void ErrorReport (string* str, error_t err_code)
{
    FILE* logs = NULL;

    #ifdef SUPERDEBUG
        logs = stderr;
    #else
        logs = fopen ("TextLogs_Diff.txt", "w");
    #endif

    switch (err_code)
    {
        case (WRONG_SYMBOL):        fprintf  (logs, "\nThere is wrong symbol in input (above pointer):\n");
                                    ParserLogs (str, logs, CURRENT);
                                    break;

        case (WRONG_OPERATION):     fprintf  (logs, "\nThere is wrong operation in input (before pointer):\n");
                                    ParserLogs (str, logs, LEFT);
                                    break;

        case (WRONG_FUNCTION):      fprintf  (logs, "\nThere is wrong function in input (before pointer):\n");
                                    ParserLogs (str, logs, LEFT);
                                    break;
    }

    fclose (logs);

    str->fuckedup = true;
}

void ParserLogs  (string* str, FILE* logs, int mode)
{
    fprintf (logs, "%s\n", str->pointer);
    for (int i = 0; i < str->offset; i++)
        fprintf (logs, " ");

    switch (mode)
    {
        case (LEFT):    fprintf (logs, "<-\n\n");
                        break;

        case (CURRENT): fprintf (logs, "^ \n\n");
                        break;
    }
}
//----------------------



// Graphic Logs
void DiffTreeLogs (Node* root)
{
    FILE* GraphicLogs = fopen ("Logs\\DiffGraphicLogs.txt", "w");
    static int call = 0;

    fprintf (GraphicLogs, "digraph %d {\n", call);
    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #ED96EC\"]\n");

    if (root)
    {
        PrintNodeLogs (root, GraphicLogs);

        if (root->left)
        {
            PrintSubTree (root->left, GraphicLogs);
            PrintArrow   (root, root->left, GraphicLogs);
        }

        if (root->right)
        {
            PrintSubTree (root->right, GraphicLogs);
            PrintArrow   (root, root->right, GraphicLogs);
        }
    }


    fprintf (GraphicLogs, "}\n");

    fclose (GraphicLogs);

    MakeOpenPhoto (call);

    call++;
}

void PrintSubTree (Node* root, FILE* GraphicLogs)
{
    if (root)
    {
        PrintNodeLogs (root, GraphicLogs);

        if (root->parent)
            PrintArrow (root, root->parent, GraphicLogs);

        if (root->left)
        {
            PrintSubTree (root->left, GraphicLogs);
            PrintArrow   (root, root->left, GraphicLogs);
        }

        if (root->right)
        {
            PrintSubTree (root->right, GraphicLogs);
            PrintArrow   (root, root->right, GraphicLogs);
        }
    }
}

void PrintNodeLogs  (Node* node, FILE* GraphicLogs)
{
    if (node)
    {
        switch (node->type)
        {
            case (TYPE_CONST):  fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = turquoise,    label = \"{%s | {%s}}\"]\n",
                                                                                    node, ConstantName (node->value.dbl_val), "TYPE_CONST");
                                break;

            case (TYPE_NUM):    fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = turquoise,    label = \"{%lg | {%s}}\"]\n",
                                                                                    node, node->value.dbl_val, "TYPE_NUM");
                                break;

            case (TYPE_OP):     fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = \" #ed96ec\", label = \"{%c | {%s}}\"]\n",
                                                                                    node, FindOperation (node), "TYPE_OP");
                                break;

            case (TYPE_VAR):    fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = turquoise,    label = \"{%s | {%s}}\"]\n",
                                                                                    node, node->value.str_val, "TYPE_VAR");
                                break;

            case (TYPE_FUNC):   fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = \"#8264ff\",  label = \"{%s | {%s}}\"]\n",
                                                                                    node, FunctionName (node->value.int_val), "TYPE_FUNC");
                                break;
        }
    }
    else
    {
        static int num_of_nulls = 1;
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = blueviolet, label = \"{NULL}\"]\n",
                                                                                0 - num_of_nulls);
        num_of_nulls++;
    }
}

void PrintArrow (Node* beginning, Node* ending, FILE* GraphicLogs)
{
    if (ending)
    {
        if (beginning->parent == ending)
            fprintf (GraphicLogs, "\"%p\" -> \"%p\" [color = black]\n", beginning, ending);
        else
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", beginning, ending);
    }
    else
    {
        static int num_of_nulls = 1;
        fprintf (GraphicLogs, "\"%p\" -> \"%d\"\n", beginning, 0 - num_of_nulls);

        num_of_nulls++;
    }
}

void MakeOpenPhoto (int call)
{
    char command_1 [MAX_COMMAND_LEN] = "";
    char command_2 [MAX_COMMAND_LEN] = "";

    sprintf (command_1, "dot -Tjpeg Logs\\DiffGraphicLogs.txt > Logs\\DiffGraphicLogs_%d.png", call);
    sprintf (command_2, "start Logs\\DiffGraphicLogs_%d.png", call);

    system (command_1);
    system (command_2);
}

char FindOperation (Node* node)
{
    switch (node->value.int_val)
    {
        case (OP_ADD):      return '+';
                            break;

        case (OP_SUB):      return '-';
                            break;

        case (OP_MUL):      return '*';
                            break;

        case (OP_DIV):      return '/';
                            break;

        case (OP_DEG):      return '^';
                            break;

        default:            assert (!"OK");
    }
}

char* ConstantName (double constant)
{
    if (constant == M_E)
    {
        return "e";
    }
    else if (constant == M_PI)
    {
        return "pi";
    }
    else
    {
        assert (!"OK");
    }
}

char* FunctionName (int func_type)
{
    switch (func_type)
    {
        case (FUNC_LN):     return "ln";

        case (FUNC_SIN):    return "sin";

        case (FUNC_COS):    return "cos";

        default:            assert (!"OK");
    }
}
//----------------------

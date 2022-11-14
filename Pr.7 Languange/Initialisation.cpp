#include "Headers/General.h"
#include "Headers/Initialisation.h"



/*** Construct-Destruct ***/


    // String
String* StringConstruct ()
{
    String* str = (String*) calloc (1, sizeof (String));

    str->pointer = NULL;
    str->offset  = 0;

    str->size = 0;

    return str;
}

void StringDestruct  (String* str)
{
    free (str->pointer);
    free (str);
}


    // Tree
Tree* TreeConstruct ()
{
    Tree* tree = (Tree*) calloc (1, sizeof (Tree));
    tree->root = NULL;

    return tree;
}

void TreeDestruct (Tree* tree)
{
    NodeDestruct (tree->root);
    free (tree);
}


    // Node
Node* NodeConstruct ()
{
    Node* node = (Node*) calloc (1, sizeof (Node));
    *node = {};

    return node;
}

void  NodeDestruct (Node* node)
{
    if (node->left)
    {
        NodeDestruct (node->left);
    }

    if (node->right)
    {
        NodeDestruct (node->right);
    }

    free (node);
}


    // Compiler
Compiler* CompilerConstruct ()
{
    Compiler* process = (Compiler*) calloc (1, sizeof (Compiler));

    process->filename = (char*) calloc (MAX_NAME_LEN, sizeof (char));

    process->name_table = TableConstruct ();

    return process;
}

void CompilerDestruct (Compiler* process)
{
    assert (process);
    assert (process->filename);
    assert (process->name_table);

    TableDestruct (process->name_table);
    free (process->filename);
    free (process);
}


    // Name Table
Function* TableConstruct ()
{
    Function* name_table = (Function*) calloc (MAX_NUM_FUNCS, sizeof (Function));

    for (int i = 0; i < MAX_NUM_FUNCS; i++)
    {
        name_table[i].name = (char*) calloc (MAX_NAME_LEN, sizeof (char));

        name_table[i].num_vars = 0;

        name_table[i].vars = (char**) calloc (MAX_NUM_NAMES, sizeof (char*));

        for (int j = 0; j < MAX_NUM_NAMES; j++)
        {
            name_table[i].vars[j] = (char*) calloc (MAX_NAME_LEN, sizeof (char));
        }
    }

    return name_table;
}

void TableDestruct (Function* name_table)
{
    for (int i = 0; i < MAX_NUM_FUNCS; i++)
    {
        free (name_table[i].name);

        for (int j = 0; j < MAX_NUM_NAMES; j++)
        {
            free (name_table[i].vars[j]);
        }
        free (name_table[i].vars);
    }
    free (name_table);
}

//---------------------------



/*** Creation of Node ***/

Node* CreateNode (int type, ... )
{
    Node* node = NodeConstruct ();

    va_list ap;
    va_start (ap, type);

    node->type  = type;

    switch (type)
    {
        case (STR_TYPE):    node->value.str_val = va_arg (ap, char*);
                            break;

        case (VAR_TYPE):    node->value.str_val = va_arg (ap, char*);
                            break;

        case (CALL_TYPE):   node->value.str_val = va_arg (ap, char*);
                            break;

        default:            node->value.dbl_val = va_arg (ap, double);
                            break;
    }

    node->left  = va_arg (ap, Node*);
    node->right = va_arg (ap, Node*);

    va_end (ap);

    return node;
}


Node* CopyNode (Node* node)
{
    switch (node->type)
    {
        case (STR_TYPE):
                            return CreateNode (node->type, node->value.str_val, NULL, NULL);

        case (VAR_TYPE):
                            return CreateNode (node->type, node->value.str_val, NULL, NULL);

        case (CALL_TYPE):
                            return CreateNode (node->type, node->value.str_val, NULL, NULL);

        default:
                            return CreateNode (node->type, node->value.dbl_val, NULL, NULL);
    }
}

//---------------------------
#include "Diff.h"

int main ()
{
    Tree* diff_tree = TreeConstruct (diff_tree);
    Tree* tree      = TreeConstruct (tree);

    tree->root = Parser ();

    // DiffTreeLogs (tree->root);
    // FormulaPrint (tree);

    Dissertation (tree);

    // diff_tree->root = Differentiate (tree->root);
    // MakeParents (diff_tree->root);

    // DiffTreeLogs (diff_tree->root);
    // FormulaPrint (diff_tree);

    // diff_tree->root = SimplifyNode (diff_tree, diff_tree->root);

    // DiffTreeLogs (diff_tree->root);
    // FormulaPrint (diff_tree);


    tree      = TreeDestruct (tree);
    diff_tree = TreeDestruct (diff_tree);

    return 0;
}



// Construct-Destruct
    // String
string* StringConstruct (string* str)
{
    str = (string*) calloc (1, sizeof (string));

    str->pointer = (char*) calloc (MAX_STRING_LEN, sizeof(char));
    str->offset  = 0;

    return str;
}

string* StringDestruct  (string* str)
{
    free (str->pointer);
    free (str);

    return NULL;
}

    // Tree & Node
Tree* TreeConstruct (Tree* tree)
{
    tree = (Tree*) calloc (1, sizeof (Tree));
    tree->root = NULL;

    return tree;
}

Tree* TreeDestruct (Tree* tree)
{
    tree->root = NodeDestruct (tree->root);
    free (tree);

    return NULL;
}

Node* NodeConstruct (Node* node)
{
    node = (Node*) calloc (1, sizeof (Node));
    *node = {};

    return node;
}

Node* NodeDestruct (Node* node)
{
    if (node->left)
        node->left = NodeDestruct (node->left);

    if (node->right)
        node->right = NodeDestruct (node->right);

    free (node);

    return NULL;
}
//----------------------


// Creation of Node
Node* CreateNode (int type, ... )
{
    Node* node = NodeConstruct (node);

    va_list ap;
    va_start (ap, type);

    /*
    if (type == TYPE_FUNC || type == TYPE_VAR)
    {
        *node = {type, NULL,  va_arg (ap, char*), NULL, va_arg (ap, Node*), va_arg (ap, Node*)};
    }
    else if (type == TYPE_NUM || type == TYPE_OP)
    {
        *node = {type, va_arg (ap, double), NULL, NULL, va_arg (ap, Node*), va_arg (ap, Node*)};
    }
    else if (type == TYPE_CONST)
    {
        *node = {type, va_arg (ap, double), va_arg (ap, char*), NULL, va_arg (ap, Node*), va_arg (ap, Node*)};
    }*/

    node->type  = type;

    switch (type)
    {
        case (TYPE_CONST):  node->value.dbl_val = va_arg (ap, double);
                            break;

        case (TYPE_NUM):    node->value.dbl_val = va_arg (ap, double);
                            break;

        case (TYPE_OP):     node->value.int_val = va_arg (ap, int);
                            break;

        case (TYPE_VAR):    node->value.str_val = va_arg (ap, char*);
                            break;

        case (TYPE_FUNC):   node->value.int_val = va_arg (ap, int);
                            break;

        default:            assert (!"OK");
    }

    node->left  = va_arg (ap, Node*);
    node->right = va_arg (ap, Node*);

    node->simplified = false;

    va_end (ap);

    return node;
}
//----------------------

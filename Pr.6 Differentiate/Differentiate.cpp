#include "Diff.h"


// Differentiate
Node* Differentiate (Node* node)
{
    switch (node->type)
    {
        case (TYPE_CONST):  return NUM (0.0);

        case (TYPE_NUM):    return NUM (0.0);

        case (TYPE_VAR):    return (strcmp(node->value.str_val, "x") == 0) ? NUM (1.0) : NUM (0.0);

        case (TYPE_OP):     return OperationDiff (node);

        case (TYPE_FUNC):   return FunctionDiff  (node);
    }
}

Node* OperationDiff (Node* node)
{
    int operation = node->value.int_val;

    switch (operation)
    {
        case (OP_ADD):      return ADD(d(L), d(R));

        case (OP_SUB):      return SUB(d(L), d(R));

        case (OP_MUL):      return ADD(MUL(d(L), c(R)), MUL(c(L), d(R)));

        case (OP_DIV):      return DIV(SUB(MUL(d(L), c(R)), MUL(c(L), d(R))), MUL(c(R), c(R)));

        case (OP_DEG):      return DegreeDiff (node);
    }
}

Node* DegreeDiff (Node* node)
{
    if (IsNumber(R))
    {
        return MUL (d(L), MUL(c(R), DEG (c(L), SUB (c(R), NUM(1.0)))));
    }
    else if (IsNumber(L))
    {
        return MUL (LN(c(L)), MUL (c(node), d(c(R))));
    }
    else
    {
        return d (DEG (EUL, MUL (LN(c(L)), c(R))));
    }
}

Node* FunctionDiff (Node* node)
{
    int func_type = node->value.int_val;

    switch (func_type)
    {
        case (FUNC_LN):     return MUL (d(R), DIV (NUM(1.0), c(R)));

        case (FUNC_SIN):    return MUL (d(R), COS(c(R)));

        case (FUNC_COS):    return MUL (d(R), MUL (NUM(-1.0), SIN(c(R))));
    }
}
//----------------------


// Help for differentiate
Node* d (Node* node)
{
    return Differentiate (node);
}

Node* c (Node* node)
{
    if (!node)
        return NULL;

    return CreateNode (node->type, node->value, c(L), c(R));
}

bool IsNumber (Node* node)
{
    switch (node->type)
    {
        case (TYPE_NUM):    return true;

        case (TYPE_CONST):  return true;

        case (TYPE_OP):     return (IsNumber (L) && IsNumber (R));

        case (TYPE_VAR):    return (strcmp(node->value.str_val, "x") == 0) ? false : true;

        case (TYPE_FUNC):   return IsNumber (R);

        default:            assert (!"OK");
    }
}

void MakeParents (Node* root)
{
    if (root->left)
    {
        root->left->parent = root;
        MakeParents (root->left);
    }

    if (root->right)
    {
        root->right->parent = root;
        MakeParents (root->right);
    }
}
//----------------------

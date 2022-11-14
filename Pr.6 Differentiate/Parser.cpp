#include "Diff.h"

#define symbol str->pointer[str->offset]


Node* Parser ()
{
    string* str = StringConstruct (str);

    gets (str->pointer);

    Node* value = GetG (str);

    bool error = str->fuckedup;
    str = StringDestruct (str);

    if (error)
        assert (!"OK");

    return value;
}


// Rules for Parser
Node* GetG (string* str)
{
    Node* value = GetExpression (str);
    if (str->fuckedup)
        return NULL;

    SyntaxRequire (str, '\0');

    return value;
}

Node* GetExpression (string* str)
{
    Node* value = GetTerm (str);

    while (symbol == '+' || symbol == '-')
    {
        int sign = symbol;
        str->offset++;

        Node* temp = GetTerm (str);

        if (str->fuckedup)
            return NULL;

        if (sign == '+')
            value = CreateNode (TYPE_OP, OP_ADD, value, temp);
        else
            value = CreateNode (TYPE_OP, OP_SUB, value, temp);

        value->left->parent  = value;
        value->right->parent = value;

    }

    return value;
}

Node* GetTerm (string* str)
{
    Node* value = GetDegree (str);

    while (symbol == '*' || symbol == '/')
    {
        int sign = symbol;
        str->offset++;

        Node* temp = GetDegree (str);

        if (str->fuckedup)
            return NULL;

        if (sign == '*')
            value = CreateNode (TYPE_OP, OP_MUL, value, temp);
        else
            value = CreateNode (TYPE_OP, OP_DIV, value, temp);

        value->left->parent  = value;
        value->right->parent = value;
    }

    return value;
}

Node* GetDegree (string* str)
{
    Node* value = GetPrimary (str);

    while (symbol == '^')
    {
        str->offset++;
        Node* temp = GetPrimary (str);

        value = CreateNode (TYPE_OP, OP_DEG, value, temp);
        value->left->parent  = value;
        value->right->parent = value;
    }

    if (str->fuckedup)
        return NULL;
    else
        return value;
}

Node* GetPrimary (string* str)
{
    SkipSpaces (str);

    Node* value = 0;
    if (symbol == '(')
    {
        str->offset++;
        value = GetExpression (str);
        SyntaxRequire (str, ')');
    }
    else if (isalpha(symbol))
    {
        value = GetVariable_Or_Function (str);
    }
    else
        value = GetNumber  (str);

    SkipSpaces (str);

    if (str->fuckedup)
        return NULL;
    else
        return value;
}

Node* GetVariable_Or_Function (string* str)
{
    Node* value = GetVariable (str);

    if (symbol == '(')
    {
        str->offset++;
        Node* arg = GetExpression (str);
        SyntaxRequire (str, ')');

        if (str->fuckedup)
            return NULL;

        value->right = arg;
        value->right->parent = value;
    }

    if (str->fuckedup)
        return NULL;
    else
        return value;
}

Node* GetVariable (string* str)
{
    char* variable = (char*) calloc (MAX_STRING_LEN, sizeof (char));

    int len = 0;
    sscanf (str->pointer + str->offset, "%[A-Z,a-z,0-9,_]%n", variable, &len);
    str->offset += len;

    double constant_value = FindConstant (variable);

    SkipSpaces (str);

    if (symbol == '(')
    {
        int function_type = FindFunction (variable);
        if (!function_type)
            ErrorReport (str, WRONG_FUNCTION);

        return CreateNode (TYPE_FUNC, function_type, NULL, NULL);
    }
    else if (!constant_value)
    {
        return CreateNode (TYPE_VAR, variable, NULL, NULL);
    }
    else
    {
        return CreateNode (TYPE_CONST, constant_value, NULL, NULL);
    }
}

Node* GetNumber (string* str)
{
    double number = 0;
    char*  end;
    number = strtod (str->pointer + str->offset, &end);

    if (str->offset == end - str->pointer)
        ErrorReport (str, WRONG_SYMBOL);
    else
        str->offset = end - str->pointer;

    if (str->fuckedup)
        return NULL;

    Node* value = CreateNode (TYPE_NUM, number, NULL, NULL);

    if (isalpha(symbol))
    {
        Node* temp = GetVariable (str);
        value = CreateNode (TYPE_OP, OP_MUL, value, temp);
        value->left->parent  = value;
        value->right->parent = value;
    }

    return value;
}
//----------------------


// Help for parsing
void SkipSpaces (string* str)
{
    while (symbol == ' ')
        str->offset++;
}

int FindFunction (char* name)
{
    if (strcmp(name, "ln") == 0)
    {
        return FUNC_LN;
    }
    else if (strcmp(name, "sin") == 0)
    {
        return FUNC_SIN;
    }
    else if (strcmp(name, "cos") == 0)
    {
        return FUNC_COS;
    }
    else
    {
        return NULL;
    }
}

double FindConstant (char* name)
{
    if (strcmp (name, "e") == 0)
    {
        return M_E;
    }
    else if (strcmp (name, "pi") == 0)
    {
        return M_PI;
    }
    else
    {
        return NULL;
    }
}
//----------------------

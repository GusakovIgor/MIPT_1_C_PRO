/*** DSL for compiler ***/


#define Current process->vertex
#define Left    Current->left
#define Right   Current->right

#define Cval    Current->value
#define Lval    Left->value
#define Rval    Right->value

#define AsmFileName process->filename
#define AsmFile     process->output
#define Func        process->current_function

#define Indent      process->indentation
const int TAB = 4;

#define KnownFuncs      process->name_table
#define NumKnownFuncs   process->num_funcs
#define KnownVars       KnownFuncs[Func].vars
#define NumKnownVars    KnownFuncs[Func].num_vars


#define PrintIndent()                                                   \
        fprintf (AsmFile, "%*c", Indent, ' ');


#define CheckVariable(index, name)                                      \
        if (index == -1)                                                \
        {                                                               \
            printf ("\nCompiling error!\n");                            \
            printf ("Undeclared variable: \"%s\"\n\n", name);           \
            assert (!"OK");                                             \
        }

#define CheckFunction(index, name)                                      \
        if (index == -1)                                                \
        {                                                               \
            printf ("\nCompiling error!\n");                            \
            printf ("Undeclared function: \"%s\"\n\n", name);           \
            assert (!"OK");                                             \
        }
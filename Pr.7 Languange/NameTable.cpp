#include "Headers/General.h"
#include "Headers/NameTable.h"
#include "Headers/CompilerDSL.h"


int FunctionIndex (Compiler* process, const char* function)
{
    for (int i = 0; i < NumKnownFuncs; i++)
    {
        if (strcmp(function, KnownFuncs[i].name) == 0)
        {
            return i;
        }
    }

    return -1;
}

int VariableIndex (Compiler* process, const char* variable)
{
    for (int i = 0; i < NumKnownVars; i++)
    {
        if (strcmp(variable, KnownVars[i]) == 0)
        {
            return i + Func*MAX_NUM_NAMES;
        }
    }

    return -1;
}


void AddFunction (Compiler* process, const char* new_function)
{
    strcpy (KnownFuncs[NumKnownFuncs++].name, new_function);
}


void AddVariable (Compiler* process, const char* new_variable)
{
    strcpy (KnownVars[NumKnownVars++], new_variable);
}
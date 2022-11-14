#include "Headers/General.h"
#include "Headers/Logs.h"
#include "Headers/CompilerDSL.h"

#include "Headers/FileProcessing.h"
#include "Headers/Initialisation.h"
#include "Headers/Parser.h"
#include "Headers/Compiler.h"
#include "Headers/NameTable.h"



int main (int argc, char* argv[])
{
    String* buff = NULL;

    if (argc > 1)
    {
        buff = FillBuff (argv[1]);
    }
    else
    {
        ErrorReport (buff, NO_NAME);
        assert (!"OK");
    }

    Tree* tree = TreeConstruct ();

    tree->root = Parser (buff);

    TreeLogs (tree->root);

    Compile (tree->root, argv[1]);

    TreeDestruct (tree);

    return 0;
}


void Compile (Node* root, const char* program)
{
    Compiler* process = CompilerConstruct ();


    strcpy (AsmFileName, program);

    ChangeFileExtension (AsmFileName, ".myasm");

    AsmFile = fopen (AsmFileName, "w");


    Current = root;

    SaveFunctions (process);


    Current = root;

    TranslateProgram (process);


    CompilerDestruct (process);
}


void SaveFunctions (Compiler* process)
{
    Func = 0;

    while (Current != NULL)
    {
        AddFunction (process, Lval.str_val);

        Current = Right;

        Func++;
    }
}


void TranslateProgram (Compiler* process)
{
    Func = 0;

    fprintf (AsmFile, "start\n");
    fprintf (AsmFile, "call :%s\n", Lval.str_val);
    fprintf (AsmFile, "hlt\n\n");

    while (Current != NULL)
    {
        Indent = 0;

        TranslateFunction (process);

        Current = Right;

        Func++;
    }
}



void TranslateFunction (Compiler* process)
{
    Node* start = Current;          // FUNC_TYPE node


    fprintf (AsmFile, "%s:\n\n", Lval.str_val);

    Current = Left;                 // STR_TYPE  node with function name

    TranslateArgs (process);


    Current = Left;                 // CODE_TYPE node

    Indent += TAB;
    TranslateCode (process);
    Indent -= TAB;


    fprintf (AsmFile, "ret\n\n\n\n");

    Current = start;
}

void TranslateArgs (Compiler* process)
{
    Node* start = Current;


    while (Right != NULL)
    {
        Current = Right;

        AddVariable (process, Cval.str_val);

        int ram_offset = VariableIndex(process, Cval.str_val);

        PrintIndent()
        fprintf (AsmFile, "pop [%d]\n", ram_offset);
    }

    fprintf (AsmFile, "\n");


    Current = start;
}

void TranslateCode (Compiler* process)
{
    Node* start = Current;


    Current = Left;             // EXP_TYPE node

    do
    {
        TranslateExpression (process);

        Current = Right;        // EXP_TYPE node
    }
    while (Current != NULL);


    Current = start;
}



void TranslateExpression (Compiler* process)
{
    Node* start = Current;


    Current = Left;

    switch (Current->type)
    {
        case DECL_TYPE:     TranslateDeclaration (process);
                            break;

        case ASGN_TYPE:     TranslateAssignment (process);
                            break;

        case INP_TYPE:      TranslateInput (process);
                            break;

        case OUT_TYPE:      TranslateOutput (process);
                            break;

        case RET_TYPE:      TranslateReturn (process);
                            break;

        case CALL_TYPE:     TranslateCall (process);
                            break;

        case LOOP_TYPE:     TranslateLoop (process);
                            break;

// YOU ARE HERE! OPEN IT
        case COMP_TYPE:     TranslateComparison (process, 0);
                            break;
    }

    fprintf (AsmFile, "\n");


    Current = start;
}



void TranslateDeclaration (Compiler* process)
{
    Node* start = Current;


    Current = Left;

    int index = VariableIndex (process, Cval.str_val);

    if (index == -1)
    {
        AddVariable (process, Cval.str_val);
    }
    else
    {
        printf ("\nCompiling error!\n");
        printf ("Conflicting declaration of variable \"%s\"\n\n", Cval.str_val);
        assert (!"OK");
    }


    Current = start;
}

void TranslateAssignment (Compiler* process)
{
    Node* start = Current;


    if (Left->type == DECL_TYPE)
    {
        Current = Left;

        TranslateDeclaration (process);
    }


    int index = VariableIndex (process, Lval.str_val);
    CheckVariable(index, Lval.str_val);


    Current = start;

    Current = Right;

    TranslateOperand (process);


    PrintIndent()
    fprintf (AsmFile, "pop[%d]\n", index);


    Current = start;
}



void TranslateInput (Compiler* process)
{
    Node* start = Current;


    Current = Left;

    if (Current->type == DECL_TYPE)
    {
        TranslateDeclaration (process);

        Current = Left;
    }


    int index = VariableIndex (process, Cval.str_val);
    CheckVariable(index, Cval.str_val)

    PrintIndent()
    fprintf (AsmFile, "in\n");
    PrintIndent()
    fprintf (AsmFile, "pop [%d]\n", index);


    Current = start;
}

void TranslateOutput (Compiler* process)
{
    Node* start = Current;


    Current = Left;

    TranslateOperand (process);

    PrintIndent()
    if (Current->type == STR_TYPE)
    {
        fprintf (AsmFile, "sout\n");
    }
    else
    {
        fprintf (AsmFile, "nout\n");
    }


    Current = start;
}



void TranslateCall (Compiler* process)
{
    int index = FunctionIndex (process, Cval.str_val);
    CheckFunction(index, Cval.str_val)

    PrintIndent()
    fprintf (AsmFile, "call :%s\n", Cval.str_val);
}

void TranslateReturn (Compiler* process)
{
    Node* start = Current;


    if (Func == 0 && (Left->type != STR_TYPE || strcmp (Lval.str_val, "song") != 0))
    {
        printf ("\nCompiling error!\n");
        printf ("In this language song (main) function should return string - \"song\"\n\n");
        assert (!"OK");
    }


    Current = Left;

    PrintIndent()
    switch (Current->type)
    {
        case NUM_TYPE:
                        fprintf (AsmFile, "push :%lf\n", Cval.dbl_val);
                        break;

        case VAR_TYPE:
                        PushVariable (process, Cval.str_val);
                        break;

        case STR_TYPE:
                        fprintf (AsmFile, "db \"%s\"\n", Cval.str_val);
                        break;
    }


    Current = start;
}



void TranslateLoop (Compiler* process)
{
    static int call = 0;
    static int last_func = -1;

    if (last_func != Func)
    {
        call = 0;
    }



    Node* start = Current;


    PrintIndent();
    fprintf (AsmFile, "loop_%d-%d:\n", Func, call);

    Indent += TAB;
    Current = Right;
    TranslateCode (process);


    Current = start;


    Current = Left;
    TranslateCondition (process);

    PrintIndent();
    PrintLoopJump (process);
    fprintf (AsmFile, " loop_%d-%d\n", Func, call);

    Indent -= TAB;
    Current = start;



    last_func = Func;
    call++;
}

void TranslateComparison (Compiler* process, int recursive)
{
    static int call = 0;
    static int max_call = 0;
    static int last_func = -1;

    if (last_func != Func)
    {
        call = 0;
    }



    Node* start = Current;


    Current = Left;
    TranslateCondition (process);
    PrintIndent();
    PrintCompareJump (process);
    fprintf (AsmFile, " else_%d-%d\n\n", Func, call + recursive);

    PrintIndent();
    fprintf (AsmFile, "if_%d-%d:\n", Func, call + recursive);
    Indent += TAB;



    Current = start->right->left;
    TranslateCode (process);

    PrintIndent();
    fprintf (AsmFile, "jmp endif_%d-%d\n\n", Func, call + recursive);

    Indent -= TAB;
    PrintIndent();
    fprintf (AsmFile, "else_%d-%d:\n", Func, call + recursive);
    Indent += TAB;



    Current = start->right->right;

    if (Current)
    {
        if (Current->type == COMP_TYPE)
        {
            TranslateComparison (process, recursive + 1);
            call--;
        }
        else if (Current->type == CODE_TYPE)
        {
            TranslateCode (process);
            max_call = call + recursive;
            printf ("\nmax_call = %d\n", max_call);
        }
    }

    Indent -= TAB;
    PrintIndent();
    fprintf (AsmFile, "endif_%d-%d:\n\n", Func, call + recursive);

    if (recursive == 0)
    {
        call = max_call;
    }

    last_func = Func;
    Current = start;
    call++;
}


void TranslateCondition (Compiler* process)
{
    Node* start = Current;


    Current = Left;
    TranslateOperand (process);
    Current = start;

    Current = Right;
    TranslateOperand (process);
    Current = start;

    PrintIndent();
    fprintf (AsmFile, "sub\n");

    PrintIndent();
    fprintf (AsmFile, "push %lf\n", 0.0);


    Current = start;
}



void TranslateMath (Compiler* process)
{
    Node* start = Current;


    Current = Left;
    TranslateOperand (process);
    Current = start;

    Current = Right;
    TranslateOperand (process);
    Current = start;


    TranslateOperation (process);


    Current = start;
}

void TranslateOperand (Compiler* process)
{
    Node* start = Current;

    switch (Current->type)
    {
        case VAR_TYPE:
                        PrintIndent()
                        PushVariable (process, Cval.str_val);
                        break;


        case STR_TYPE:
                        PrintIndent()
                        fprintf (AsmFile, "db \"%s\"\n", Cval.str_val);
                        break;


        case NUM_TYPE:
                        PrintIndent()
                        fprintf (AsmFile, "push %lf\n", Cval.dbl_val);
                        break;


        case MATH_TYPE: TranslateMath (process);
                        break;
    }


    Current = start;
}

void TranslateOperation (Compiler* process)
{
    if (!Current)
    {
        return;
    }


    PrintIndent()
    switch ((int) Cval.dbl_val)
    {
        case OP_ADD:
                        fprintf (AsmFile, "add\n");
                        break;

        case OP_SUB:
                        fprintf (AsmFile, "sub\n");
                        break;

        case OP_MUL:
                        fprintf (AsmFile, "mul\n");
                        break;

        case OP_DIV:
                        fprintf (AsmFile, "div\n");
                        break;

        case OP_DEG:
                        fprintf (AsmFile, "pow\n");
                        break;

        // case OP_SQRT:
        //              fprintf (AsmFile, "sqrt\n");
        //              break;
    }

    fprintf (AsmFile, "\n");
}



void PrintLoopJump (Compiler* process)
{
    switch ((int) Cval.dbl_val)
    {
        case OP_EQUAL:
                        fprintf (AsmFile, "je");
                        break;

        case OP_NOTEQUAL:
                        fprintf (AsmFile, "jne");
                        break;

        case OP_GREATER:
                        fprintf (AsmFile, "ja");
                        break;

        case OP_LESS:
                        fprintf (AsmFile, "jb");
                        break;
    }
}

void PrintCompareJump (Compiler* process)
{
    switch ((int) Cval.dbl_val)
    {
        case OP_EQUAL:
                        fprintf (AsmFile, "jne");
                        break;

        case OP_NOTEQUAL:
                        fprintf (AsmFile, "je");
                        break;

        case OP_GREATER:
                        fprintf (AsmFile, "jb");
                        break;

        case OP_LESS:
                        fprintf (AsmFile, "ja");
                        break;
    }
}



void PushVariable (Compiler* process, char* name)
{
    int index = VariableIndex(process, name);
    CheckVariable(index, name);

    fprintf (AsmFile, "push [%d]\n", index);
}
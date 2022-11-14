#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

typedef int error_t;

const int MAX_STRING_LEN  = 100;

const int MAX_COMMAND_LEN = 100;

const int MAX_PHRASE_LEN  = 100;


struct string
{
    bool fuckedup;

    char* pointer;
    int   offset;
};

struct Node
{
    int type;

    union {
        int    int_val;
        double dbl_val;
        char*  str_val;
    } value;

    Node* parent;
    Node* left;
    Node* right;

    bool simplified;
};

struct Tree
{
    Node* root;
    FILE* home;
};


// Enums
enum diff_errors { WRONG_OPERATION = 1,
                   WRONG_SYMBOL    = 2,
                   WRONG_FUNCTION  = 3
};

enum diff_debug_modes { LEFT    = 1,
                        CURRENT = 2,
                        RIGHT   = 3
};

enum diff_node_types { TYPE_OP    = 1,
                       TYPE_VAR   = 2,
                       TYPE_NUM   = 3,
                       TYPE_FUNC  = 4,
                       TYPE_CONST = 5
};

enum diff_operation_types { OP_ADD = 1,
                            OP_SUB = 2,
                            OP_MUL = 4,
                            OP_DIV = 5,
                            OP_DEG = 7
};

enum Diff_function_typed  { FUNC_LN  = 1,
                            FUNC_SIN = 2,
                            FUNC_COS = 3
};
//----------------------


// DSL


#define L node->left
#define R node->right
#define Lval node->left->value.dbl_val
#define Rval node->right->value.dbl_val

#define ADD(left, right)                                \
    CreateNode (TYPE_OP, OP_ADD, left, right)

#define SUB(left, right)                                \
    CreateNode (TYPE_OP, OP_SUB, left, right)

#define MUL(left, right)                                \
    CreateNode (TYPE_OP, OP_MUL, left, right)

#define DIV(left, right)                                \
    CreateNode (TYPE_OP, OP_DIV, left, right)

#define DEG(left, right)                                \
    CreateNode (TYPE_OP, OP_DEG, left, right)


#define NUM(number)                                     \
    CreateNode (TYPE_NUM, number, NULL, NULL)

#define EUL                                             \
    CreateNode (TYPE_CONST, M_E,  NULL, NULL)


#define SIN(arg)                                        \
    CreateNode (TYPE_FUNC, FUNC_SIN, NULL, arg)

#define COS(arg)                                        \
    CreateNode (TYPE_FUNC, FUNC_COS, NULL, arg)

#define LN(arg)                                         \
    CreateNode (TYPE_FUNC, FUNC_LN,  NULL, arg)
//----------------------



// Creation
string* StringConstruct (string* str);
string* StringDestruct  (string* str);

Tree* TreeConstruct (Tree* tree);
Tree* TreeDestruct  (Tree* tree);

Node* NodeConstruct (Node* node);
Node* NodeDestruct  (Node* node);

Node* CreateNode    (int type, ...);
//----------------------


// Parser
Node* Parser ();

Node* GetG (string* str);
Node* GetExpression (string* str);
Node* GetTerm       (string* str);
Node* GetDegree     (string* str);

Node* GetVariable_Or_Function (string* str);

Node* GetPrimary    (string* str);
Node* GetVariable   (string* str);
Node* GetNumber     (string* str);

void   SkipSpaces   (string* str);

int    FindFunction (char* name);
double FindConstant (char* name);
//----------------------


// Differentiate
Node* Differentiate (Node* node);

Node* OperationDiff (Node* node);
Node* DegreeDiff    (Node* node);

Node* FunctionDiff  (Node* node);

bool  IsNumber      (Node* node);
void  MakeParents   (Node* root);
Node* d (Node* node);
Node* c (Node* node);
//----------------------


// Simplifying
Node* SimplifyNode      (Tree* tree, Node* node);

Node* SimplifyOperation (Node* node);
Node* SimplifyFunction  (Node* node);

Node* SimplifyAdd (Node* node);
Node* SimplifySub (Node* node);
Node* SimplifyMul (Node* node);
Node* SimplifyDiv (Node* node);
Node* SimplifyDeg (Node* node);

Node* SimplifyLn (Node* node);

Node* ReduceFraction  (Node* node);

Node* BothNumCase      (Node* node);
Node* AnotherBranch    (Node* node);
Node* MakeNodeRootless (Node* side);
Node* ZeroCase         (Node* node);

double OperationResult (Node* node);

int FindGCD (int num_1, int num_2);
//----------------------


// Logs
void SyntaxRequire  (string* str, char request);
void ErrorReport    (string* str, error_t err_code);
void ParserLogs     (string* str, FILE* logs, int mode);

void DiffTreeLogs   (Node* root);
void PrintSubTree   (Node* root, FILE* GraphicLogs);
void PrintNodeLogs  (Node* node, FILE* GraphicLogs);
void PrintArrow     (Node* beginning, Node* ending, FILE* GraphicLogs);
void MakeOpenPhoto  (int call);

char FindOperation  (Node* node);
char* FunctionName  (int func_type);
char* ConstantName  (double constant);
//----------------------

// Output
void Dissertation (Tree* tree);

void FormulaPrint (Tree* tree);
void CompileLaTeX (int call);

void PrintHeader            (FILE* LaTeX);
void PrintNode              (Node* node, FILE* LaTeX);
void PrintOperation         (Node* node, FILE* LaTeX);
void PrintSubNode           (Node* sub_node, FILE* LaTeX, int operation);
void PrintSign              (int operation, FILE* LaTeX);
void PrintFuncArg           (Node* node, FILE* LaTeX);
//----------------------

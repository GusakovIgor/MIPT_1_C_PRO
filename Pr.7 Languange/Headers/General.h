#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>



const int MAX_NAME_LEN    = 100;
const int MAX_COMMAND_LEN = 300;
const int MAX_NUM_NAMES   = 100;
const int MAX_NUM_FUNCS   = 100;



struct String;

struct Tree;
struct Node;

struct Functions;
struct Compiler;



typedef int error_t;



struct String
{
    bool error_occured;

    char* pointer;
    int   offset;
    int   line;

    size_t size;
};


struct Tree
{
    Node* root;
};

struct Node
{
    int type;

    union {
        double dbl_val;
        char*  str_val;
    } value;

    Node* parent;
    Node* left;
    Node* right;
};


struct Function
{
    char* name;

    int num_vars;

    char** vars;
};



struct Compiler
{
    char* filename;

    FILE* output;

    Node* vertex;


    int num_funcs;

    int current_function;

    Function* name_table;


    int indentation;
};



enum node_types {
                    FUNC_TYPE,      //+/ new function                           |   song/sample
                    CODE_TYPE,      //+/ a brunch of code                       |   {...} and EXP when it's son of loop
                    EXP_TYPE,       //+/ one line of code that is not simple    |   assignment, declaration, return, compare, output

                    DECL_TYPE,      //+/ new variable                           |   new x
                    ASGN_TYPE,      //+/ definition of variable                 |   choose x as y

                    INP_TYPE,       //+/ input                                  |   record x from input
                    OUT_TYPE,       //+/ output                                 |   echo ("...")    or   echo (x)

                    RET_TYPE,       //+/ returning from function                |   save x   or   save song
                    CALL_TYPE,      //+/ calling a functions                    |

                    COMP_TYPE,      //+/ compare                                |   pitch
                    COND_TYPE,      //+/ condition                              |   > == != <
                    IFEL_TYPE,      //+/ contains if/else code                  |   {...} {...}
                    LOOP_TYPE,      //+/ loop                                   |   back_echo   or   reverberation

                    MATH_TYPE,      //+/ math operations                        |   + - * / ^
                    MFUNC_TYPE,     //+/ math functions                         |   sin, cos, ln
                    CONST_TYPE,     //+/ math constants
                    NUM_TYPE,       //+/ number                                 |   any double
                    STR_TYPE,       //+/ string                                 |   "..."
                    VAR_TYPE        //+/ string                                 |   variable
                };



// Node values are 0 if they are not measurable, string if str_type, double if num_type,
// and one of those if math_type:

enum node_values {
                    OP_ADD,
                    OP_SUB,
                    OP_MUL,
                    OP_DIV,
                    OP_DEG,
                    OP_SQRT,

                    OP_EQUAL,
                    OP_NOTEQUAL,
                    OP_GREATER,
                    OP_LESS,

                    FUNC_LN,
                    FUNC_SIN,
                    FUNC_COS,

                    CONST_EXP,
                    CONST_PI
};


enum parser_errors {
                    NO_NAME,
                    NO_FILE,
                    WRONG_SYMBOL,
                    WRONG_WORD,
                    WRONG_NAME,
                    WRONG_FUNC,
                    WRONG_IFEL,
                    WRONG_STATEMENT,
                    WRONG_ARGUMENT
};


enum check_mods {
                    SYMBOL,
                    WORD
};
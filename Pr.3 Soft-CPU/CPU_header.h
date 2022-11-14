#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <memory.h>
#include <ctype.h>
#include "MyStack/Stack.h"

const int MAX_FILENAME     = 300;      // For program->name
const int MAX_LABLE_NAME   = 15;
const int MAX_CODE_LEN     = 100000;  // For program->bin_buff
const int MAX_COMAND_LEN   = 300;
const int MAX_NUM_LABLES   = 500;
const int STACK_START_SIZE = 100;     // For arrays with names of comands
const int NUM_REGISTERS    = 6;       // For arrays with names of registers
const int VERSION          = 7;

const int RAM_SIZE         = 1000*8;    // = 8*10^3
const int DATA_SIZE        = 1000*100;  // = 1*10^5
const int VRAM_SIZE        = 2000*2000; // = 4*10^6
const int pix_size         = 1;

const int MODE_NUMBER = 0;
const int MODE_WORD   = 1;


/*** DEFINING COMMANDS ***/
#define DEF_CMD(name, num, arg, code)   \
                CMD_##name = num,       \

enum comands
{
    #include "Commands.h"
};

#undef DEF_CMD

// END OF DEFINING COMMANDS


enum registers {    VRAM = 0,
                    RAX = 1,
                    RBX = 2,
                    RCX = 3,
                    RDX = 4,
                    CAT = 5,
                    MYAU = 6     };


struct text;
struct CPU;
struct FileHeader;
struct label;


/*** TextProcessing file ***/

text* ProgramConstructor (char* name);
void  ProgramDestructor  (text** program);

size_t GetText      (text* program);
size_t GetFileSize  (const char* name);
size_t ReadText     (text* program, size_t size);

size_t CountLines        (char* text, size_t num_symbols);
void   CleanAllComments  (char* text, size_t num_symbals);
int    CommentCleaner    (char* text, size_t num_symbals, int cur_symbal);

void ChangeFileExtension (char* filename, const char* new_extension);

//---------------------------------------------------



/*** Assembler file ***/

label* CreateLabels ();
void Assembler      (text* program, char* bin_buff, label* labels, int ofs);
void ReadWord       (char* dest, char* src, int* pos);
void SkipSpaces     (char* buff, int* pos);

void Sign_maker     (char* bin_buff, int* ofs);
void MakeLable      (label* labels, char* temp, char* check, int* ofs);
int  SearchLable    (label* labels, char* temp);

void ComplicComProcessing (char* buff, int* pos, char* bin_buff, int* ofs, label* labels, int num);
void PushOrPop      (char* buff, int* pos, char* bin_buff, int* ofs);                // Thanks Uliana for that functions
void Jumps          (char* buff, int* pos, char* bin_buff, int* ofs, label* labels);       // (I was trying to make it all in DEF_CMD macro)
void DefiningBytes  (char* buff, int* pos, char* bin_buff, int* ofs);
void Drawing        (char* buff, int* pos, char* bin_buff, int* ofs);
char ChooseMode     (char* arg, char* temp);
void ArgInsert      (char* bin_buff, int* ofs, char* temp);
int  FindRegNumber  (char* temp);
void ConvertEscapeSeq (char* string);

//--------------------------------------------------



/*** Calculator file ***/

CPU* CPU_Construct  (char* file_name);
CPU* CPU_Destruct    (CPU* processor);
void CodeReader      (CPU* processor, char* file_name);
void SignatureCheck  (CPU* processor);
void StackDebugPrint (CPU* processor);
double  ArgGetter    (CPU* processor, int mode, double* RAM);
double* RAM_Maker    ();

//--------------------------------------------------


/*** Structures ***/

struct text
{
    int num_lines;
    char* name;
    char* buff;
};


struct CPU
{
    MyStack* stack;
    MyStack* calls;

    int pc;

    double* registers;

    char* code;
    size_t code_size;
};


struct FileHeader
{
    const char signature[3];
    int version;
};


struct label
{
    int adr;
    char name[MAX_LABLE_NAME];
};
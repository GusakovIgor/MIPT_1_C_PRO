#ifndef TX_USE_SPEAK
    #define TX_USE_SPEAK
#endif

#include "TXLib.h"
#include "List\\List.h"


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <locale.h>

typedef int error_t;

const int MAX_TEXT_LEN = 100;
const int MAX_HEIGHT   = 20;

enum Errors {ALLOCATION_ERROR = 0, WRONG_NODE_PTR, INCORRECT_MODE, TREE_FILE_ERROR, WRONG_FILE_FORMAT, WRONG_ANSWER, WRONG_ELEM_NAME};

enum Modes {GAME = 1,
            DEFINITION  = 2,
            COMPARISION = 3,
            TREE        = 4,
            EXIT        = 5,
            BREAK       = 6};

enum Moods {HELLO = 0,
            ASK   = 1,
            RIGHT = 3,
            SAD   = 6,
            WRONG = 10};

struct Tree
{
    Node* root;
};



// Construct-Destruct
Tree* Construct ();
Tree* Destruct  (Tree* tree);

Node* NodeConstruct (Node* vertex);
Node* NodeDestruct  (Node* vertex);
//----------------------


// Functions
HDC*   PikachuIsGettingReady   (HDC* Pikachu);
char** PikachuIsLearningToTalk (char** phrases);

int  ModeDetector (const char*);

void Akinator (Tree* tree, int mode, HDC Pikachu[]);

void  PlayGame (Node* root, HDC Pikachu[]);
void  Checker  (Node* root, HDC Pikachu[]);
Node* InsertNode (Node* vertex);

void  Definition (Tree* tree);
Node* Find (Node* root, char* temp);
int   Filler (List* lst, Node* object, Node* root, int index);

void  Comparision (Tree* tree);
void  PrintProperties (List* lst_1, List* lst_2);
void  PrintDifference (List* lst, char* temp);

void SayGoodbye    (HDC* Pikachu);
void Delete_images (HDC Pikachu_ask[]);

int  Random (int border);
//----------------------


// Logs
void ErrorReport  (error_t err_code, const char* func);
void PrintModes   (FILE* StdLogs);


void LogsMaker    (Node* root, char* mode);
void PrintSubTree (Node* root, FILE* GraphicLogs, int mode);

//----------------------


// TreeFileProcessing
Tree*  ReadTree ();

size_t TextReader (const char* name, char* text, size_t size);
size_t SizeGetter (const char* name);
size_t TreeProcessing (char* buff, size_t num_symbols);

Node* ScanPositive (Node* vertex, char* buff);
void  WriteTree    (Node* tree, FILE* database);
//----------------------


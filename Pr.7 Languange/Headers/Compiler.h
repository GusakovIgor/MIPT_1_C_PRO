/*** Compiler in asm (in Compiler.cpp) ***/

void Compile (Node* root, const char* program);

void SaveFunctions (Compiler* process);


void TranslateProgram    (Compiler* process);

void TranslateFunction   (Compiler* process);

void TranslateArgs       (Compiler* process);

void TranslateCode       (Compiler* process);

void TranslateExpression (Compiler* process);


void TranslateDeclaration (Compiler* process);

void TranslateAssignment  (Compiler* process);

void TranslateInput       (Compiler* process);

void TranslateOutput      (Compiler* process);


void TranslateCall   (Compiler* process);

void TranslateReturn (Compiler* process);


void TranslateLoop          (Compiler* process);

void TranslateComparison    (Compiler* process, int recursive);

void TranslateCondition     (Compiler* process);



void TranslateMath      (Compiler* process);

void TranslateOperand   (Compiler* process);

void TranslateOperation (Compiler* process);


void PrintLoopJump      (Compiler* process);

void PrintCompareJump   (Compiler* process);


void PushVariable   (Compiler* process, char* name);


//----------------------
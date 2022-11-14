/*** Parsing (in Parser.cpp) ***/

Node* Parser  (String* buff);

Node* GetProg (String* buff);

//---------------------------



/*** Functions ***/

Node* GetFunc (String* buff);

Node* GetArgs (String* buff);

Node* GetCode (String* buff);

//---------------------------



/*** Expressions ***/

Node* GetExp  (String* buff);


Node* GetVarDecl (String* buff, char* func);

Node* GetVarInit (String* buff, char* func);


Node* GetEcase   (String* buff, char* func);

Node* GetRcase   (String* buff, char* func);

Node* GetBcase   (String* buff, char* func);


Node* GetInput   (String* buff, char* func);

Node* GetOutput  (String* buff, char* func);


Node* GetForwLoop (String* buff, char* func);

Node* GetBackLoop (String* buff, char* func);


Node* GetCompare (String* buff, char* func);

Node* GetOp (String* buff);


Node* GetCall (String* buff, char* func);

Node* GetSave (String* buff, char* func);

//---------------------------



/*** Names ***/

Node* GetFuncName (String* buff);

Node* GetVarName  (String* buff);

char* GetWord (String* buff);

//---------------------------



/*** Primary ***/

Node* GetString (String* buff);

Node* GetNumber (String* buff);

Node* GetVariable (String* buff);

//---------------------------



/*** Math ***/

Node* GetMath (String* buff);

Node* GetExpression (String* buff);

Node* GetTerm (String* buff);

Node* GetDegree (String* buff);

Node* GetPrimary (String* buff);

Node* GetVariable_Or_Function (String* buff);

//---------------------------






/*** Help (in Parser.cpp) ***/

void SkipSpaces (String* buff);

int    FindFunction (char* name);

double FindConstant (char* name);

//---------------------------
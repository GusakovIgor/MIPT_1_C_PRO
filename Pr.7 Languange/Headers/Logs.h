/*** Errors Processing (in LangLogs.cpp) ***/

bool SyntaxCheck        (String* buff, int type, ...);

void SyntaxCheckFailure (String* buff, int type, ...);


void ErrorReport    (String* buff, error_t err_code);

void PrintErrorLine (String* buff, error_t err_code, FILE*logs);

char* FindLineStart (String* buff, int* indent);

//----------------------



/*** Graphic Logs (in LangLogs.cpp) ***/

void TreeLogs      (Node* root);

void PrintSubTree  (Node* root, FILE* GraphicLogs);

void PrintNodeLogs (Node* node, FILE* GraphicLogs);

void PrintArrow    (Node* beginning, Node* ending, FILE* GraphicLogs);

void MakeOpenPhoto (int call);


const char* MathOutput    (double value);
//----------------------
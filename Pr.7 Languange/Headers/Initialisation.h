/*** Constructors/Destructors (in Input.cpp) ***/

String*     StringConstruct ();
void        StringDestruct  (String* str);

Tree*       TreeConstruct ();
void        TreeDestruct  (Tree* tree);

Node*       NodeConstruct ();
void        NodeDestruct  (Node* node);

Compiler*   CompilerConstruct ();
void        CompilerDestruct  (Compiler* process);

Function*   TableConstruct ();
void        TableDestruct  (Function* name_table);


Node* CreateNode    (int type, ...);
Node* CopyNode      (Node* node);

//----------------------
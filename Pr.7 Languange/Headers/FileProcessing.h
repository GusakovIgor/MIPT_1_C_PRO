/*** Reading from file (in InputProc.cpp) ***/

String* FillBuff   (const char* fname);


size_t GetFileSize (const char* fname);

size_t GetFileText (const char* fname, size_t fsize, char* text);


void TextPreProcessing (size_t size, char* text);



void ChangeFileExtension (char* filename, const char* new_extension);

//----------------------
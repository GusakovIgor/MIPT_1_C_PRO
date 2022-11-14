#include "Headers/General.h"
#include "Headers/Logs.h"

#include "Headers/Initialisation.h"
#include "Headers/FileProcessing.h"


String* FillBuff   (const char* fname)
{
    size_t fsize = GetFileSize (fname);

    String* buff = StringConstruct ();

    if (fsize >= 0)
    {
        buff->pointer = (char*) calloc (fsize + 1, sizeof (char));
        buff->size = GetFileText (fname, fsize, buff->pointer);
    }
    else
    {
        ErrorReport (buff, NO_FILE);
    }

    return buff;
}


size_t GetFileSize (const char* fname)
{
    FILE* file = fopen (fname, "r");

    if (!file)
        return -1;

    struct stat finfo;
    stat (fname, &finfo);

    size_t size = finfo.st_size;

    fclose (file);

    return size;
}


size_t GetFileText (const char* fname, size_t fsize, char* text)
{
    FILE* input = fopen (fname, "r");

    size_t num_symb = fread (text, sizeof(char), fsize, input);

    fclose (input);

    TextPreProcessing (num_symb, text);
    text[num_symb] = '\0';

    return num_symb;
}



void TextPreProcessing (size_t size, char* text)
{
    for (int i = 0; i < size; i++)
    {
        if (text[i] == '\n' || text[i] == '\r')
        {
            text[i] = '\0';
        }
    }
}



void ChangeFileExtension (char* filename, const char* new_extension)
{
    char* extension = strchr (filename, '.');

    if (strlen(filename) - strlen(extension) + strlen(new_extension) + 1 <= MAX_NAME_LEN)
    {
        strcpy (extension, new_extension);
    }
    else
    {
        printf ("Your program name is too long: \"%s\"\n", filename);
        printf ("Please rename file, so it will be no longer than %ld symbols\n", MAX_NAME_LEN - strlen(new_extension) - 1);

        assert (!"OK");
    }
}
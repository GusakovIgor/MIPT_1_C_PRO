#include "CPU_header.h"

text* ProgramConstructor (char* name)
{
    text* program = (text*) calloc (1, sizeof(text));
    assert (program);

    program->name = (char*) calloc (MAX_FILENAME, sizeof(char));
    assert (program->name);

    assert (strlen(name) < MAX_FILENAME);
    strcpy (program->name, name);


    size_t num_symbols = GetText (program);

    CleanAllComments (program->buff, num_symbols);

    program->num_lines = CountLines (program->buff, num_symbols);

    ChangeFileExtension (program->name, ".bin");


    return program;
}

void ProgramDestructor (text** program)
{
    free ((*program)->name);
    free ((*program)->buff);
    free (*program);

    *program = NULL;
}



size_t GetText (text* program)
{
    size_t size = GetFileSize (program->name);

    program->buff = (char*) calloc (size + 1, sizeof(char));
    assert (program->buff != NULL);

    size_t num_symbols = ReadText (program, size);
    assert (num_symbols);

    return num_symbols;
}

size_t GetFileSize (const char* name)
{
    FILE* file = fopen (name, "r");

    struct stat finfo;
    stat(name, &finfo);
    size_t size = finfo.st_size;

    fclose (file);

    return size;
}

size_t ReadText (text* program, size_t size)
{
    FILE* file = fopen (program->name, "r");

    size_t num_symbols = fread (program->buff, sizeof(char), size, file);
    *(program->buff + num_symbols) = '\0';

    fclose (file);

    return num_symbols;
}


size_t CountLines (char* text, size_t num_symbols)
{
    assert (text);
    size_t num_lines = 1;

    for (int i = 0; i < num_symbols; i++)
    {
        if (text[i] == '\n')
        {
            num_lines++;
        }
    }

    return num_lines;
}


void CleanAllComments (char* text, size_t num_symbols)
{
    assert (text);

    for (int i = 0; i < num_symbols; i++)
    {
        if (text[i] == ';')
        {
            i = CommentCleaner (text, num_symbols, i);
        }
    }
}


int CommentCleaner (char* text, size_t num_symbols, int cur_symbal)
{
    assert (text[cur_symbal] == ';');

    while (text[cur_symbal] != '\n' && cur_symbal < num_symbols)
    {
        text[cur_symbal] = ' ';
        cur_symbal++;
        if (text[cur_symbal] == ';')
        {
            printf("ERROR in comments, you can't put one in another");
            assert(!"OK");
        }
    }

    return cur_symbal;
}


void ChangeFileExtension (char* filename, const char* new_extension)
{
    char* extension = strchr (filename, '.');

    if (strlen(filename) - strlen(extension) + strlen(new_extension) + 1 <= MAX_FILENAME)
    {
        strcpy (extension, new_extension);
    }
    else
    {
        printf ("Your program name is too long: \"%s\"\n", filename);
        printf ("Please rename file, so it will be no longer than %d symbols\n", MAX_FILENAME - strlen(new_extension) - 1);

        assert (!"OK");
    }
}
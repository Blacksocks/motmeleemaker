#include "file.h"

void getDimFile(FILE * f, dim_t * dim)
{
    unsigned char c;
    int nlf = 1; // no line feed
    dim->h = 0;
    dim->w = 0;
    fseek(f, 0, SEEK_SET);
    while ((c = getc(f)) != (unsigned char)EOF)
        if(c != '\n')
        {
            if(dim->h == 0)
            {
                dim->w++;
                for(int i = 0; i < nbOfBytesInChar(c) - 1; i++)
                    getc(f);
            }
            nlf = 1;
        }
        else if(nlf == 1)
        {
            dim->h++;
            nlf = 0;
        }
}

void getWDimFile(FILE * f, int * dim)
{
    unsigned char c;
    int nlf = 1; // no line feed
    int count = 0;
    fseek(f, 0, SEEK_SET);
    dim[0] = 0;
    while ((c = getc(f)) != (unsigned char)EOF)
    {
        if(c != '\n')
        {
            dim[count]++;
            for(int i = 0; i < nbOfBytesInChar(c) - 1; i++)
                getc(f);
            nlf = 1;
        }
        else if(nlf == 1)
        {
            dim[++count] = 0;
            nlf = 0;
        }
    }
}

void getGrid(FILE * f, char_t * grid)
{
    unsigned char c;
    int count = 0;
    fseek(f, 0, SEEK_SET);
    while ((c = getc(f)) != (unsigned char)EOF)
        if(c != '\n')
        {
            grid[count].c[0] = c;
            for(int i = 1; i < nbOfBytesInChar(c); i++)
                grid[count].c[i] = getc(f);
            count++;
        }
}

void getWords(FILE * f, word_t * words)
{
    char c;
    int count = 0;
    int idx = 0;
    int byteIdx;
    fseek(f, 0, SEEK_SET);
    while ((c = getc(f)) != EOF)
    {
        if(c != '\n')
        {
            byteIdx = 0;
            words[idx].w[count].c[byteIdx++] = c;
            for (int i = 0; i < nbOfBytesInChar(c) - 1; i++)
                words[idx].w[count].c[byteIdx++] = fgetc(f);
            count++;
        }
        else if(count != 0)
        {
            idx++;
            count = 0;
        }
    }
}

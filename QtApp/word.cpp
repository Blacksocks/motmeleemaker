#include <stdio.h>

#include "word.h"

int nbOfBytesInChar(unsigned char val)
{
    if (val < 128) return 1;
    if (val < 224) return 2;
    if (val < 240) return 3;
    return 4;
}

void printW(word_t * word)
{
    for(int i = 0; i < word->l; i++)
        for(int k = 0; k < nbOfBytesInChar(word->w[i].c[0]); k++)
            putchar(word->w[i].c[k]);
    printf("\n");
}

int cmpWaUS(word_t * word, unsigned char * in, int inLen)
{
    int count = 0;
    int cIdx;
    for(int i = 0; i < word->l; i++)
    {
        cIdx = 0;
        for(int j = 0; j < nbOfBytesInChar(word->w[i].c[0]); j++)
        {
            if(word->w[i].c[cIdx++] != in[count++])
                return 0;
            if(count >= inLen)
                return 0;
        }
    }
    return 1;
}

int getUCLen(unsigned char * array, int maxLen)
{
    int i = 0;
    int count = 0;
    while(array[i] != 0 && i < maxLen)
    {
        i += nbOfBytesInChar(array[i]);
        count++;
    }
    return count;
}

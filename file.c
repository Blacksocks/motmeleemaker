#include "file.h"
#include "word.h"

#define POS(grid,x,y)	grid->g[grid->w * (y) + x]

/* Return number of bytes used to store a char in utf8
** val:			value to examine
*/
int nbOfBytesInChar(unsigned char val)
{
    if (val < 128) return 1;
    if (val < 224) return 2;
    if (val < 240) return 3;
    return 4;
}

int getNbLines(FILE * f)
{
	char c;
	int nlf = 0;
	int nbLines = 0;
	fseek(f, 0, SEEK_SET);
	while ((c = getc(f)) != EOF)
		if(c != '\n')
			nlf = 1;
		else if(nlf == 1)
		{
			nbLines++;
			nlf = 0;
		}
	return nbLines;
}

void getWordsLen(FILE * f, int * len)
{
	unsigned char c;
	int count = 0;
	int idx = 0;
	fseek(f, 0, SEEK_SET);
	while((c = getc(f)) != (unsigned char)EOF)
	{
		if(c != '\n')
		{
			count++;
			for (int i = 0; i < nbOfBytesInChar(c) - 1; i++)
	            fgetc(f);
		}
		else if(count != 0)
		{
			len[idx++] = count;
			count = 0;
		}
	}
}

void getWords(FILE * f, char_t ** list)
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
			list[idx][count].c[byteIdx++] = c;
			for (int i = 0; i < nbOfBytesInChar(c) - 1; i++)
				list[idx][count].c[byteIdx++] = fgetc(f);
			count++;
		}
		else if(count != 0)
		{
			idx++;
			count = 0;
		}
	}
}

void saveGrid(FILE * f, const t_grid * grid)
{
	for(int j = 0; j < grid->ly; j++)
	{
		for(int i = 0; i < grid->lx; i++)
			for (int k = 0; k < nbOfBytesInChar(POS(grid,i,j).c[0]); k++)
	            fprintf(f, "%c", POS(grid,i,j).c[k]);
		fputc('\n', f);
	}
}

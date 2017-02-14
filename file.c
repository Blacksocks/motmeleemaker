#include "file.h"

#define POS(grid,x,y)	grid->g[grid->w * (y) + x]

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
	char c;
	int count = 0;
	int idx = 0;
	fseek(f, 0, SEEK_SET);
	while ((c = getc(f)) != EOF)
	{
		if(c != '\n')
			count++;
		else if(count != 0)
		{
			len[idx++] = count;
			count = 0;
		}
	}
}

void getWords(FILE * f, char ** list)
{
	char c;
	int count = 0;
	int idx = 0;
	fseek(f, 0, SEEK_SET);
	while ((c = getc(f)) != EOF)
	{
		if(c != '\n')
		{
			list[idx][count] = c;
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
			fputc(POS(grid,i,j), f);
		fputc('\n', f);
	}
}

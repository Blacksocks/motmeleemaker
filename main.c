#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "word.h"
#include "grid.h"

#define NBTRY			(10)

/* Return absolute value
** x: input value
*/
int abs(int x)
{
	return(x >= 0 ? x : -x);
}

int main(int argc, char * argv[])
{
	int nbWords = 0;
	// input strings
	char ** list;
	// length of input string
	int * listLen;
	if(argc < 2 || argc > 3)
	{
		printf("Usage: main filein[, size]\n  filein: (string) input text file with one word per line\n  size: (int) size of the square grid\n");
		return 1;
	}
	else
	{
		// get word list from file
		int c;
		FILE *file;
		file = fopen(argv[1], "r");
		if (file)
		{
			int nlf = 0;
			// get number of line
			while ((c = getc(file)) != EOF)
				if(c != '\n')
					nlf = 1;
				else if(nlf == 1)
				{
					nbWords++;
					nlf = 0;
				}
			// get memory for list
			list = malloc(sizeof(char *) * nbWords);
			listLen = malloc(sizeof(int) * nbWords);
			// get memory for words
			int count = 0;
			int idx = 0;
			fseek(file, 0, SEEK_SET);
			while ((c = getc(file)) != EOF)
			{
				if(c != '\n')
					count++;
				else if(count != 0)
				{
					list[idx] = malloc(sizeof(char) * count + 1);
					for (int a = 0; a < count + 1; ++a)
						list[idx][a] = 0;
					listLen[idx++] = count;
					count = 0;
				}
			}
			// recopy words into list
			fseek(file, 0, SEEK_SET);
			count = 0;
			idx = 0;
			while ((c = getc(file)) != EOF)
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
			fclose(file);
		}
		else
		{
			printf("[ERROR] File cannot be readen\n");
			return 1;
		}
	}
	int gridLenX, gridLenY;
	if(argc == 3)
	{
		// set grid length
		gridLenX = atoi(argv[2]);
		gridLenY = gridLenX;
	}
	else
	{
		// set grid length
		gridLenX = listLen[0]; // max of word length
		for(int i = 1; i < nbWords; i++)
			if(listLen[i] > gridLenX)
				gridLenX = listLen[i];
		gridLenY = nbWords;
		if(gridLenX > gridLenY) // make square grid
			gridLenY = gridLenX;
		else
			gridLenX = gridLenY;
	}
	const int gridLen = gridLenX * gridLenY;
	// init grid
	char gridArray[gridLen];
	t_grid grid = {gridArray, gridLenX, gridLenY, gridLenX};
	char tmpGridArray[gridLen];
	t_grid tmpGrid = {tmpGridArray, gridLenX, gridLenY, gridLenX};
	for(int i = 0; i < gridLen; i++)
		grid.g[i] = EMPTY;
	// sort list from longer to shorter
	sort(list, listLen, nbWords);
	// print input strings ordered
	for(int i = 0; i < nbWords; i++)
		printf("%s\n", list[i]);
	// initialise random function
	time_t t;
	srand((unsigned) time(&t));
	// coefficient which caracterise grid dimensions
	// penalise no square grids
	int dimCoef = grid.lx + grid.ly + abs(grid.lx - grid.ly);
	// generate grid
	int noResult = 1;
	// Several try are made and the best is kept in order to find a small grid
	for(int i = 0; i < NBTRY; i++)
	{
		for(int i = 0; i < gridLen; i++)
			tmpGrid.g[i] = EMPTY;
		int success = gridGenerator(&tmpGrid, list, listLen, nbWords);
		if(success)
		{
			int tmpX1, tmpY1, tmpX2, tmpY2;
			getGridSize(&tmpGrid, &tmpX1, &tmpY1, &tmpX2, &tmpY2);
			// if tmpGrid dimensions are smaller than grid ones
			int tmpW = tmpX2 - tmpX1;
			int tmpH = tmpY2 - tmpY1;
			int tmpDimCoef = tmpW + tmpH + abs(tmpW - tmpH);
			if(tmpDimCoef < dimCoef || noResult)
			{
				// replace grid into tmpGrid
				gridCopy(&grid, &tmpGrid);
				dimCoef = tmpDimCoef;
			}
			noResult = 0;
		}
	}
	if(noResult)
	{
		printf("No configuratin were found.\nSuggestion: retry or force grid dimensions.\n");
		return 1;
	}
	resizeGrid(&grid);
	char letters[MAXLETLEN];
	int lettersLen = 0;
	getLettersFromWords(list, listLen, nbWords, letters, &lettersLen);
	fillGrid(&grid, letters, lettersLen);
	gridDisplay(&grid);
	// free
	for(int i = 0; i < nbWords; i++)
		free(list[i]);
	free(list);
	free(listLen);
	return 0;
}

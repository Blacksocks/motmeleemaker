#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "word.h"
#include "grid.h"
#include "file.h"

#define NBTRY		(10)
#define MAXINT(a,b)	((a > b) ? a : b)
#define SQ(x)		(x * x)

/* Return absolute value
** x:				input value
*/
int abs(int x)
{
	return(x >= 0 ? x : -x);
}

/* Return max value into an integer array
** list:			integer array
** len:				array length
*/
int getMaxInt(int * list, int length)
{
	int res = list[0]; // max of word length
	for(int i = 1; i < length; i++)
		if(list[i] > res)
			res = list[i];
	return res;
}

int main(int argc, char * argv[])
{
	// input strings
	char ** list;
	// length of input string
	int * listLen;
	if(argc < 2 || argc > 3)
	{
		printf("Usage: main filein[, size]\n  filein: (string) input text file with one word per line\n  size: (int) size of the square grid\n");
		return 1;
	}

	// get word list from file
	FILE *file;
	file = fopen(argv[1], "r");
	if(!file)
	{
		printf("[ERROR] File cannot be readen\n");
		return 1;
	}
	int nbWords = getNbLines(file);
	// allocate memory for list
	list = malloc(sizeof(char *) * nbWords);
	listLen = malloc(sizeof(int) * nbWords);
	getWordsLen(file, listLen);
	// allocate memory for words
	for(int i = 0; i < nbWords; i++)
		list[i] = malloc(sizeof(char) * (listLen[i] + 1));
	// recopy words into list
	getWords(file, list);
	fclose(file);

	// init grid
	const int gridSize = (argc == 3) ? atoi(argv[2]) : MAXINT(getMaxInt(listLen, nbWords), nbWords);
	char gridArray[SQ(gridSize)];
	t_grid grid = {gridArray, gridSize, gridSize, gridSize};
	char tmpGridArray[SQ(gridSize)];
	t_grid tmpGrid = {tmpGridArray, gridSize, gridSize, gridSize};
	for(int i = 0; i < SQ(gridSize); i++)
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
	int dimCoef = grid.lx + grid.ly;
	// generate grid
	int noResult = 1;
	// Several try are made and the best is kept in order to find a small grid
	for(int i = 0; i < NBTRY; i++)
	{
		for(int j = 0; j < SQ(gridSize); j++)
			tmpGrid.g[j] = EMPTY;
		int success = gridGenerator(&tmpGrid, list, listLen, nbWords);
		if(success)
		{
			int tmpX1, tmpY1, tmpX2, tmpY2;
			getGridSize(&tmpGrid, &tmpX1, &tmpY1, &tmpX2, &tmpY2);
			// if tmpGrid dimensions are smaller than grid ones
			int tmpDimCoef = tmpX2 - tmpX1 + tmpY2 - tmpY1;
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

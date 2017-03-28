#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "word.h"
#include "grid.h"
#include "file.h"

#define NBTRY		(10)

#define MAX(a,b)	((a > b) ? a : b)
#define SQ(x)		(x * x)

char_t empty = {"\0\0\0."};

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
	if(argc < 3 || argc > 4)
	{
		printf("argc = %d\n", argc);
		printf("Usage: main filein, fileout[, size]\n"
		"  filein: (string) input text file with one word per line\n"
		"  fileout: (string) output text file\n"
		"  size: (int) size of the square grid\n");
		return 1;
	}

	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "Current working dir: %s\n", cwd);
	else
		perror("getcwd() error");

	// get word list from file
	FILE * file = fopen(argv[1], "r");
	if(!file)
	{
		printf("[ERROR] Input file \"%s\" error: %s\n", argv[1], strerror(errno));
		return 1;
	}
	int nbWords = getNbLines(file);
	// allocate memory for input words
	char_t ** list = malloc(sizeof(char_t *) * nbWords);
	int * listLen = malloc(sizeof(int) * nbWords);
	if(!list || !listLen)
	{
		printf("[ERROR] Malloc failed\n");
		return 1;
	}
	getWordsLen(file, listLen);
	// allocate memory for words
	for(int i = 0; i < nbWords; i++)
	{
		list[i] = malloc(sizeof(char_t) * listLen[i]);
		// init list content to 0
		for(int j = 0; j < listLen[i]; j++)
			for(int k = 0; k < CHARSIZE; k++)
				list[i][j].c[k] = 0;
		if(!list[i])
		{
			printf("[ERROR] Malloc failed\n");
			return 1;
		}
	}
	// recopy words into list
	getWords(file, list);
	fclose(file);

	// init grid
	const int gridSize = (argc == 4) ? atoi(argv[3]) : MAX(getMaxInt(listLen, nbWords), nbWords);
	char_t gridArray[SQ(gridSize)];
	t_grid grid = {gridArray, gridSize, gridSize, gridSize};
	char_t tmpGridArray[SQ(gridSize)];
	t_grid tmpGrid = {tmpGridArray, gridSize, gridSize, gridSize};
	for(int i = 0; i < SQ(gridSize); i++)
		setChar(&grid.g[i], &empty);

	// sort list from longer to shorter
	sort(list, listLen, nbWords);
	// initialise random function
	time_t t;
	srand((unsigned) time(&t));

	// generate grid
	int noResult = 1;
	// Several try are made and the best is kept in order to find a small grid
	for(int i = 0; i < NBTRY; i++)
	{
		for(int j = 0; j < SQ(gridSize); j++)
			setChar(&tmpGrid.g[j], &empty);
		int success = gridGenerator(&tmpGrid, list, listLen, nbWords);
		if(!success)
			continue;
		if(noResult)
		{
			noResult = 0;
			gridCopy(&grid, &tmpGrid);
		}
		else
			gridReplaceIfSmaller(&tmpGrid, &grid);
		normalizeGrid(&grid);
	}
	if(noResult)
	{
		printf("No configuratin were found.\nSuggestion: retry or force grid dimensions.\n");
		return 1;
	}
	char_t letters[MAXLETLEN];
	int lettersLen = 0;
	getLettersFromWords(list, listLen, nbWords, letters, &lettersLen);
	fillGrid(&grid, letters, lettersLen);

	// write grid into ouput file
	file = fopen(argv[2], "w");
	if(!file)
	{
		printf("[ERROR] Output file cannot be readen\n");
		gridDisplay(&grid);
		return 1;
	}
	saveGrid(file, &grid);
	fclose(file);

	// free
	for(int i = 0; i < nbWords; i++)
		free(list[i]);
	free(list);
	free(listLen);
	return 0;
}

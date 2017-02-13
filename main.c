#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "word.h"

#define EMPTY			'.'
#define NBTRY			(10)

// get random value on x axis
// r:rotation, l: string length, m: maximum
#define RDMX(r,l,m)		BTW(r,l,3,5) + rand() % (m - NEQ2(r,l,2,6))
// is different from two values, multiply per k
#define NEQ2(x,k,a,b)	((x == a || x == b) ? 0 : k)
// is between two values, multiply per k
#define BTW(x,k,a,b)	((x >= a && x <= b) ? k : 0)
// Make a step at direction r on x and y axis
// r = 0, from left to right, increase in clockwise
#define ROT(r,x,y)		switch(r){case 0:x++;break;case 1:x++;y++;break;\
						case 2:y++;break;case 3:x--;y++;break;\
						case 4:x--;break;case 5:x--;y--;break;\
						case 6:y--;break;case 7:x++;y--;break;}

/* Return absolute value
** x:			input value
*/
int abs(int x)
{
	return(x >= 0 ? x : -x);
}

/* Insert a word into a grid smartly
** grid:		grid here the ord must be insterted
** gridLenX:	width of the grid
** gridLenY:	height of the grid
** word:		current word
** wordLen:		lenght of the word
** return: insertion successful ?
*/
int insertWord(char * grid, int gridLenX, int gridLenY, char * word, int wordLen)
{
	int maxPosX, minPosX, maxPosY, minPosY;
	int wordBreak; // is word into grid ?
	int emptyBreak; // used for first loop
	int tmpX, tmpY;
	int posX, posY;
	wordBreak = 0;
	// init rotation
	// rotation is a random number between 0 and 7
	// 0: normal reading; from left to right
	// turn in clockwise
	int rot = rand() % 8;
	// first loop; try to insert new word into a previous word
	for(int r = 0; r < 7 && !wordBreak; r++)
	{
		// init position
		minPosX = BTW(rot,wordLen-1,3,5);
		maxPosX = gridLenX - 1 - NEQ2(rot,wordLen-1,2,6); // size X
		minPosY = BTW(rot,wordLen-1,5,7);
		maxPosY = gridLenY - 1 - NEQ2(rot,wordLen-1,0,4); // size Y
		// find random position
		if(maxPosX == 0) posX = minPosX;
		else posX = minPosX + rand() % maxPosX;
		if(maxPosY == 0) posY = minPosY;
		else posY = minPosY + rand() % maxPosY;
		maxPosX += minPosX;
		maxPosY += minPosY;
		for(int y = minPosY; y <= maxPosY && !wordBreak; y++)
		{
			for(int x = minPosX; x <= maxPosX && !wordBreak; x++)
			{
				// is word into another ?
				tmpX = posX; tmpY = posY;
				emptyBreak = 1;
				for(int j = 0; j < wordLen; j++)
					if(grid[gridLenX*tmpY+tmpX] == EMPTY)
						ROT(rot,tmpX,tmpY)
					else
						emptyBreak = 0;
				// if not, pass to next position and/or rotation
				if(!emptyBreak)
				{
					// check if word could be here
					tmpX = posX; tmpY = posY;
					emptyBreak = 1;
					for(int j = 0; j < wordLen; j++)
					{
						char gridVal = grid[gridLenX*tmpY+tmpX];
						if(gridVal == EMPTY || gridVal == word[j])
							ROT(rot,tmpX,tmpY)
						else
							emptyBreak = 0;
					}
					// if word can be here, pass to next word
					if(emptyBreak)
					{
						// pass to next word
						wordBreak = 1;
						// and write it into grid
						tmpX = posX; tmpY = posY;
						for(int j = 0; j < wordLen; j++)
						{
							grid[gridLenX*tmpY+tmpX] = word[j];
							ROT(rot,tmpX,tmpY)
						}
					}
				}
				// increment posX
				if(++posX > maxPosX)
					posX = minPosX;
			}
			// increment posY
			if(++posY > maxPosY)
				posY = minPosY;
		}
		// increment rot
		if(++rot == 8)
			rot = 0;
	}
	// second loop; try to insert new word everywhere in the grid
	for(int r = 0; r < 7 && !wordBreak; r++)
	{
		// init position
		minPosX = BTW(rot,wordLen-1,3,5);
		maxPosX = gridLenX - 1 - NEQ2(rot,wordLen-1,2,6); // size X
		minPosY = BTW(rot,wordLen-1,5,7);
		maxPosY = gridLenY - 1 - NEQ2(rot,wordLen-1,0,4); // size Y
		// find random position
		if(maxPosX == 0) posX = minPosX;
		else posX = minPosX + rand() % maxPosX;
		if(maxPosY == 0) posY = minPosY;
		else posY = minPosY + rand() % maxPosY;
		maxPosX += minPosX;
		maxPosY += minPosY;
		for(int y = minPosY; y <= maxPosY && !wordBreak; y++)
		{
			for(int x = minPosX; x <= maxPosX && !wordBreak; x++)
			{
				// is word into another ?
				tmpX = posX; tmpY = posY;
				emptyBreak = 1;
				for(int j = 0; j < wordLen; j++)
					if(grid[gridLenX*tmpY+tmpX] == EMPTY)
						ROT(rot,tmpX,tmpY)
					else
						emptyBreak = 0;
				// if yes, print it and pass to next word
				if(emptyBreak)
				{
					// pass to next word
					wordBreak = 1;
					// and write it into grid
					tmpX = posX; tmpY = posY;
					for(int j = 0; j < wordLen; j++)
					{
						grid[gridLenX*tmpY+tmpX] = word[j];
						ROT(rot,tmpX,tmpY)
					}
				}
				// increment posX
				if(++posX > maxPosX)
					posX = minPosX;
			}
			// increment posY
			if(++posY > maxPosY)
				posY = minPosY;
		}
		// increment rot
		if(++rot == 8)
			rot = 0;
	}
	return 1;
}

/* Fill grid with random letters
** grid:		grid here the ord must be insterted
** gridLenX:	width of the grid
** gridLenY:	height of the grid
** letters:		characters which could be used
** lettersLen:	lenght of letters array
*/
void fillGrid(char * grid, int gridLenX, int gridLenY, char * letters, int letterLen)
{
	for(int i = 0; i < gridLenY; i++)
		for(int j = 0; j < gridLenX; j++)
		{
			// if character isn't EMPTY, don't fill it
			if(grid[i*gridLenX+j] != EMPTY)
				continue;
			// get random letter into letters and fill grid with it
			grid[i*gridLenX+j] = letters[rand() % letterLen];
		}
}


/* Generate a "mot melee" game from strings array
** grid: 			output array of char
** gridLenX: 		grid width
** gridLenY: 		grid height
** list: 			main input, array of strings
** listLen: 		len of each string
** listLenLen: 		number of words
** return: does a problem occured ? (exemple: grid too small)
*/
int gridGenerator(
	char * 			grid,
	const int 		gridLenX,
	const int 		gridLenY,
	char ** 		list,
	const int * 	len,
	const int 		listLen
){
	for(int i = 0; i < listLen; i++)
		if(!insertWord(grid, gridLenX, gridLenY, list[i], len[i]))
			return 0;
	return 1;
}

/* Grid printer function
** grid:			grid displayed
** gridLenX: 		grid width
** gridLenY: 		grid height
*/
void print(char * grid, int gridLenX, int gridLenY)
{
	printf("  .");
	for(int i = 0; i < gridLenX; i++)
		printf("%c%d", (i < 10) ? ' ' : i / 10 + '0', i % 10);
	printf("\n");
	for(int j = 0; j < gridLenY; j++)
	{
		printf("%c%d| ", (j < 10) ? ' ' : j / 10 + '0', j % 10);
		for(int i = 0; i < gridLenX; i++)
			printf("%c ", grid[j*gridLenX + i]);
		printf("\n");
	}
}

/* Copy a grid into another
** grid1;			output grid
** grid2:			input grid
** gridLenX: 		grid width
** gridLenY: 		grid height
*/
void gridCopy(char * grid1, const char * grid2, int gridLenX, int gridLenY)
{
	for(int j = 0; j < gridLenY; j++)
		for(int i = 0; i < gridLenX; i++)
			grid1[j*gridLenX+i] = grid2[j*gridLenX+i];
}

/* Calculate dimenstion of non empty window of grid
** grid:			grid displayed
** gridLenX: 		grid width
** gridLenY: 		grid height
** x1:				window X position
** y1:				window Y position
** x2:				window width + window X position
** y2:				window height + window Y positin
*/
void getGridSize(char * grid, int gridLenX, int gridLenY, int * x1, int * y1, int * x2, int * y2)
{
	*x1 = gridLenX - 1;
	*y1 = gridLenY - 1;
	*x2 = 0;
	*y2 = 0;
	for(int tmpY = 0; tmpY < gridLenY; tmpY++)
		for(int tmpX = 0; tmpX < gridLenX; tmpX++)
		{
			if(grid[gridLenX*tmpY + tmpX] == EMPTY)
				continue;
			if(tmpX < *x1) *x1 = tmpX;
			if(tmpX > *x2) *x2 = tmpX;
			if(tmpY < *y1) *y1 = tmpY;
			if(tmpY > *y2) *y2 = tmpY;
		}
}

/* Resize grid
** grid:			grid displayed
** gridLenX: 		grid width
** gridLenY: 		grid height
*/
void resizeGrid(char * grid, int * gridLenX, int * gridLenY)
{
	int x1, y1, x2, y2;
	getGridSize(grid, *gridLenX, *gridLenY, &x1, &y1, &x2, &y2);
	int w = x2 - x1 + 1;
	int h = y2 - y1 + 1;
	// shift grid [-x1, -y1]
	for(int j = 0; j < h; j++)
		for(int i = 0; i < w; i++)
			grid[*gridLenX*j+i] = grid[*gridLenX*(j+y1)+i+x1];
	// reset rest of the grid
	for(int j = 0; j < *gridLenY; j++)
		for(int i = 0; i < *gridLenX; i++)
			if(i >= w || j >= h)
				grid[*gridLenX*j+i] = EMPTY;
	*gridLenX = w;
	*gridLenY = h;
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
	char grid[gridLen];
	char tmpGrid[gridLen];
	for(int i = 0; i < gridLen; i++)
		grid[i] = EMPTY;
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
	int dimCoef = gridLenX + gridLenY + abs(gridLenX - gridLenY);
	// generate grid
	int noResult = 1;
	// Several try are made and the best is kept in order to find a small grid
	for(int i = 0; i < NBTRY; i++)
	{
		for(int i = 0; i < gridLen; i++)
			tmpGrid[i] = EMPTY;
		int success = gridGenerator(tmpGrid, gridLenX, gridLenY, list, listLen, nbWords);
		if(success)
		{
			int tmpX1, tmpY1, tmpX2, tmpY2;
			getGridSize(tmpGrid, gridLenX, gridLenY, &tmpX1, &tmpY1, &tmpX2, &tmpY2);
			// if tmpGrid dimensions are smaller than grid ones
			int tmpW = tmpX2 - tmpX1;
			int tmpH = tmpY2 - tmpY1;
			int tmpDimCoef = tmpW + tmpH + abs(tmpW - tmpH);
			if(tmpDimCoef < dimCoef || noResult)
			{
				// replace grid into tmpGrid
				gridCopy(grid, tmpGrid, gridLenX, gridLenY);
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
	// resize grid
	resizeGrid(grid, &gridLenX, &gridLenY);
	char letters[MAXLETLEN];
	int lettersLen = 0;
	getLettersFromWords(list, listLen, nbWords, letters, &lettersLen);
	fillGrid(grid, gridLenX, gridLenY, letters, lettersLen);
	print(grid, gridLenX, gridLenY);
	// free
	for(int i = 0; i < nbWords; i++)
		free(list[i]);
	free(list);
	free(listLen);
	return 0;
}

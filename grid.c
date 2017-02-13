#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

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

int gridGenerator(char * grid, const int gridLenX, const int gridLenY, char ** list, const int * len, const int listLen)
{
	for(int i = 0; i < listLen; i++)
		if(!insertWord(grid, gridLenX, gridLenY, list[i], len[i]))
			return 0;
	return 1;
}

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

void gridCopy(char * grid1, const char * grid2, int gridLenX, int gridLenY)
{
	for(int j = 0; j < gridLenY; j++)
		for(int i = 0; i < gridLenX; i++)
			grid1[j*gridLenX+i] = grid2[j*gridLenX+i];
}

void gridDisplay(char * grid, int gridLenX, int gridLenY)
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

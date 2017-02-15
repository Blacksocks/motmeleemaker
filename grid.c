#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "word.h"

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
#define POS(grid,x,y)	grid->g[grid->w * (y) + x]

extern char_t empty;

/* Write a word into a grid
** grid:		grid target
** word: 		word to print
** x:			x position of the word
** y:			y position of the word
** rot:			rotation of the word
*/
void writeWord(t_grid * grid, word_t * word, int x, int y, int rot)
{
	for(int j = 0; j < word->len; j++)
	{
		setChar(&POS(grid,x,y), &word->w[j]);
		ROT(rot,x,y)
	}
}

/* Insert a word into a grid smartly
** grid:		grid where the words must be inserted
** word:		current word
** wordLen:		lenght of the word
** return: insertion successful ?
*/
int insertWord(t_grid * grid, word_t * word)
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
		minPosX = BTW(rot,word->len-1,3,5);
		maxPosX = grid->lx - 1 - NEQ2(rot,word->len-1,2,6); // size X
		minPosY = BTW(rot,word->len-1,5,7);
		maxPosY = grid->ly - 1 - NEQ2(rot,word->len-1,0,4); // size Y
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
				for(int j = 0; j < word->len; j++)
					if(cmpChar(&POS(grid,tmpX,tmpY), &empty))
						ROT(rot,tmpX,tmpY)
					else
						emptyBreak = 0;
				// if not, pass to next position and/or rotation
				if(!emptyBreak)
				{
					// check if word could be here
					tmpX = posX; tmpY = posY;
					emptyBreak = 1;
					for(int j = 0; j < word->len; j++)
					{
						char_t gridVal = POS(grid,tmpX,tmpY);
						if(cmpChar(&gridVal, &empty) || cmpChar(&gridVal, &word->w[j]))
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
						writeWord(grid, word, posX, posY, rot);
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
		minPosX = BTW(rot,word->len-1,3,5);
		maxPosX = grid->lx - 1 - NEQ2(rot,word->len-1,2,6); // size X
		minPosY = BTW(rot,word->len-1,5,7);
		maxPosY = grid->ly - 1 - NEQ2(rot,word->len-1,0,4); // size Y
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
				for(int j = 0; j < word->len; j++)
					if(cmpChar(&POS(grid,tmpX,tmpY), &empty))
						ROT(rot,tmpX,tmpY)
					else
						emptyBreak = 0;
				// if yes, print it and pass to next word
				if(emptyBreak)
				{
					// pass to next word
					wordBreak = 1;
					// and write it into grid
					writeWord(grid, word, posX, posY, rot);
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

int gridGenerator(t_grid * grid, char_t ** list, const int * len, const int listLen)
{

	for(int i = 0; i < listLen; i++)
	{
		word_t word = {list[i], len[i]};
		if(!insertWord(grid, &word))
			return 0;
	}
	return 1;
}

void fillGrid(t_grid * grid, const char_t * letters, const int letterLen)
{
	for(int i = 0; i < grid->ly; i++)
		for(int j = 0; j < grid->lx; j++)
		{
			// if character isn't EMPTY, don't fill it
			if(!cmpChar(&POS(grid,j,i), &empty))
				continue;
			// get random letter into letters and fill grid with it
			setChar(&POS(grid,j,i), &letters[rand() % letterLen]);
		}
}

void normalizeGrid(t_grid * grid)
{
	int x1, y1, x2, y2;
	getGridSize(grid, &x1, &y1, &x2, &y2);
	int w = x2 - x1 + 1;
	int h = y2 - y1 + 1;
	// shift grid [-x1, -y1]
	for(int j = 0; j < h; j++)
		for(int i = 0; i < w; i++)
			for(int k = 0; k < CHARSIZE; k++)
				POS(grid,i,j).c[k] = POS(grid,i+x1,j+y1).c[k];
	// reset rest of the grid
	for(int j = 0; j < grid->ly; j++)
		for(int i = 0; i < grid->lx; i++)
			if(i >= w || j >= h)
				setChar(&POS(grid,i,j), &empty);
	grid->lx = w;
	grid->ly = h;
}

void getGridSize(const t_grid * grid, int * x1, int * y1, int * x2, int * y2)
{
	*x1 = grid->lx - 1;
	*y1 = grid->ly - 1;
	*x2 = 0;
	*y2 = 0;
	for(int tmpY = 0; tmpY < grid->ly; tmpY++)
		for(int tmpX = 0; tmpX < grid->lx; tmpX++)
		{
			if(cmpChar(&POS(grid,tmpX,tmpY), &empty))
				continue;
			if(tmpX < *x1) *x1 = tmpX;
			if(tmpX > *x2) *x2 = tmpX;
			if(tmpY < *y1) *y1 = tmpY;
			if(tmpY > *y2) *y2 = tmpY;
		}
}

void gridCopy(t_grid * grid1, const t_grid * grid2)
{
	grid1->lx = grid2->lx;
	grid1->ly = grid2->ly;
	for(int j = 0; j < grid2->ly; j++)
		for(int i = 0; i < grid2->lx; i++)
			for(int k = 0; k < CHARSIZE; k++)
				POS(grid1,i,j).c[k] = POS(grid2,i,j).c[k];
}

void gridDisplay(const t_grid * grid)
{
	printf("  .");
	for(int i = 0; i < grid->lx; i++)
		printf("%c%d", (i < 10) ? ' ' : i / 10 + '0', i % 10);
	printf("\n");
	for(int j = 0; j < grid->ly; j++)
	{
		printf("%c%d| ", (j < 10) ? ' ' : j / 10 + '0', j % 10);
		for(int i = 0; i < grid->lx; i++)
		{
			for(int k = 0; k < CHARSIZE; k++)
				putchar(POS(grid,i,j).c[k]);
			printf(" ");
		}
		printf("\n");
	}
}

int gridReplaceIfSmaller(const t_grid * tmpGrid, t_grid * grid)
{
	int gridLen = grid->lx + grid->ly;
	int tmpX1, tmpY1, tmpX2, tmpY2;
	getGridSize(tmpGrid, &tmpX1, &tmpY1, &tmpX2, &tmpY2);
	// if tmpGrid dimensions are smaller than grid ones
	int tmpGridLen = tmpX2 - tmpX1 + tmpY2 - tmpY1 + 2;
	if(tmpGridLen < gridLen)
	{
		// replace grid into tmpGrid
		gridCopy(grid, tmpGrid);
		return 1;
	}
	return 0;
}

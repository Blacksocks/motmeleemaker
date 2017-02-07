#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NBWORDS		(5)
#define EMPTY		'.'

// get random value on x axis
// r:rotation, l: string length, m: maximum
#define RDMX(r,l,m)	BTW(r,l,3,5) + rand() % (m - NEQ2(r,l,2,6))
// is different from two values, multiply per k
#define NEQ2(x,k,a,b)	((x == a || x == b) ? 0 : k)
// is between two values, multiply per k
#define BTW(x,k,a,b)	((x >= a && x <= b) ? k : 0)
// Make a step at direction r on x and y axis
// r = 0, from left to right, increase in clockwise
#define ROT(r,x,y)	switch(r){case 0:x++;break;case 1:x++;y++;break;\
					case 2:y++;break;case 3:x--;y++;break;\
					case 4:x--;break;case 5:x--;y--;break;\
					case 6:y--;break;case 7:x++;y--;break;}
/* Calculate dimenstion of non empty window of grid
** winX, winY, winW, winH: window dimensions
** grid: grid array
** gridLenX, gridLenY: grid size
*/
void recalculateWin(
	int * 			winX1,
	int * 			winY1,
	int * 			winX2,
	int * 			winY2,
	char * 			grid,
	int 			gridLenX,
	int 			gridLenY
){
	*winX1 = gridLenX - 1;
	*winY1 = gridLenY - 1;
	*winX2 = 0;
	*winY2 = 0;
	for(int tmpY = 0; tmpY < gridLenY; tmpY++)
		for(int tmpX = 0; tmpX < gridLenX; tmpX++)
		{
			if(grid[gridLenX*tmpY + tmpX] == EMPTY)
				continue;
			if(tmpX < *winX1) *winX1 = tmpX;
			if(tmpX > *winX2) *winX2 = tmpX;
			if(tmpY < *winY1) *winY1 = tmpY;
			if(tmpY > *winY2) *winY2 = tmpY;
		}
}

/* Generate a "mot melee" game from strings array
** grid: 			output array of char
** gridLenX: 		grid width
** gridLenY: 		grid height
** list: 			main input, array of strings
** listLen: 		len of each string
** listLenLen: 		number of words
*/
void gridGenerator(
	char * 			grid,
	const int 		gridLenX,
	const int 		gridLenY,
	const char ** 	list,
	const int * 	len,
	const int 		listLen
){
	// initialise random function
	time_t t;
	srand((unsigned) time(&t));
	// rotation is a random number between 0 and 7
	// 0: normal reading; from left to right
	// turn in clockwise
	int rot = rand() % 8;
	// get random position for first word
	int posX = BTW(rot,len[0],3,5) + rand() % (gridLenX - NEQ2(rot,len[0],2,6));
	int posY = BTW(rot,len[0],5,7) + rand() % (gridLenY - NEQ2(rot,len[0],0,4));
	printf("r:%d, x:%d, y:%d\n", rot, posX, posY);
	// write first word into grid
	for(int i = 0; i < len[0]; i++)
	{
		grid[gridLenX*posY+posX] = list[0][i];
		ROT(rot,posX,posY)
	}
	// calcul minimum window where values of grid are not null
	int winX1, winY1, winX2, winY2;
	recalculateWin(&winX1, &winY1, &winX2, &winY2, grid, gridLenX, gridLenY);
	printf("win: [%d,%d] [%d,%d]\n", winX1, winY1, winX2, winY2);
	int maxPosX, minPosX, maxPosY, minPosY;
	for(int i = 0; i < listLen; i++)
	{
		// init rotation
		rot = rand() % 8;
		// init position
		minPosX = BTW(rot,len[i],3,5);
		maxPosX = gridLenX - NEQ2(rot,len[i],2,6); // pos X length
		minPosY = BTW(rot,len[i],5,7);
		maxPosY = gridLenY - NEQ2(rot,len[i],0,4); // pos Y length
		// find random position
		posX = minPosX + rand() % maxPosX;
		posY = minPosY + rand() % maxPosY;
		maxPosX += minPosX;
		maxPosY += minPosY;
		// first loop; try to insert new word into a previous word
		for(int r = 0; r < 7; r++)
		{
			for(int y = winY1; y < winY2; y++)
			{
				for(int x = winX1; x < winX2; x++)
				{
					// MUST BE COMPLETED

					if(++posX > maxPosX)
						posX = minPosX;
				}
				if(++posY > maxPosY)
					posY = minPosY;
			}
			if(++rot == 8)
				rot = 0;
		}
		// second loop; try to insert new word everywhere in the grid
		for(int r = 0; r < 7; r++)
		{
			for(int y = winY1; y < winY2; y++)
			{
				for(int x = winX1; x < winX2; x++)
				{
					// MUST BE COMPLETED

					if(++posX > maxPosX)
						posX = minPosX;
				}
				if(++posY > maxPosY)
					posY = minPosY;
			}
			if(++rot == 8)
				rot = 0;
		}
	}
}

int main(void)
{
	// input strings
	const char * list[NBWORDS];
	list[0] = "test";
	list[1] = "bonjour";
	list[2] = "space space";
	list[3] = "thisisaverylongword";
	list[4] = "littleword";
	// length of input string
	const int listLen[] = {4, 7, 11, 19, 10};
	// print input words
	for(int i = 0; i < NBWORDS; i++)
	{
		for(int j = 0; j < listLen[i]; j++)
			printf("%c", list[i][j]);
		printf("\n");
	}
	// grid length
	int gridLenX = listLen[0]; // max of word length
	for(int i = 1; i < NBWORDS; i++)
		if(listLen[i] > gridLenX)
			gridLenX = listLen[i];
	int gridLenY = NBWORDS;
	if(gridLenX > gridLenY) // make square grid
		gridLenY = gridLenX;
	else
		gridLenX = gridLenY;
	const int gridLen = gridLenX * gridLenY;
	// init grid
	char grid[gridLen];
	for(int i = 0; i < gridLen; i++)
		grid[i] = EMPTY;

	gridGenerator(grid, gridLenX, gridLenY, list, listLen, NBWORDS);

	// print grid
	for(int j = 0; j < gridLenY; j++)
	{
		for(int i = 0; i < gridLenX; i++)
			printf("%c ", grid[j*gridLenX + i]);
		printf("\n");
	}

	return 0;
}

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
	int maxPosX, minPosX, maxPosY, minPosY;
	int wordBreak; // is word into grid ?
	int emptyBreak; // used for first loop
	int tmpX, tmpY;
	for(int i = 0; i < listLen; i++)
	{
		wordBreak = 0;
		// init rotation
		rot = rand() % 8;
		// init position
		minPosX = BTW(rot,len[i],3,5);
		maxPosX = gridLenX - NEQ2(rot,len[i],2,6); // size X
		minPosY = BTW(rot,len[i],5,7);
		maxPosY = gridLenY - NEQ2(rot,len[i],0,4); // size Y
		// find random position
		posX = minPosX + rand() % maxPosX;
		posY = minPosY + rand() % maxPosY;
		maxPosX += minPosX;
		maxPosY += minPosY;
		// first loop; try to insert new word into a previous word
		for(int r = 0; r < 7 && !wordBreak; r++)
		{
			for(int y = minPosY; y <= maxPosY && !wordBreak; y++)
			{
				for(int x = minPosX; x <= maxPosX && !wordBreak; x++)
				{
					// is word into another ?
					tmpX = x; tmpY = y;
					emptyBreak = 1;
					for(int j = 0; j < len[i]; j++)
					{
						if(grid[gridLenX*posY+tmpY] == EMPTY)
							ROT(rot,tmpX,tmpY)
						else
							emptyBreak = 0;
					}
					// if not, pass to next position and/or rotation
					if(emptyBreak)
						continue;

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
		for(int r = 0; r < 7 && !wordBreak; r++)
		{
			for(int y = minPosY; y <= maxPosY && !wordBreak; y++)
			{
				for(int x = minPosX; x <= maxPosX && !wordBreak; x++)
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

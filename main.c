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



	// MUST TRIER LIST FROM LONGER TO SMALL WORD




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
	for(int i = 1; i < listLen; i++)
	{
		wordBreak = 0;
		// init rotation
		rot = rand() % 8;
		// first loop; try to insert new word into a previous word
		for(int r = 0; r < 7 && !wordBreak; r++)
		{
			// init position
			minPosX = BTW(rot,len[i]-1,3,5);
			maxPosX = gridLenX - 1 - NEQ2(rot,len[i]-1,2,6); // size X
			minPosY = BTW(rot,len[i]-1,5,7);
			maxPosY = gridLenY - 1 - NEQ2(rot,len[i]-1,0,4); // size Y
			// find random position
			if(maxPosX == 0) posX = minPosX;
			else posX = minPosX + rand() % maxPosX;
			if(maxPosY == 0) posY = minPosY;
			else posY = minPosY + rand() % maxPosY;
			maxPosX += minPosX;
			maxPosY += minPosY;
			printf("%s - rot:%d ", list[i], rot);
			printf("minPosX:%d minPosY:%d maxPosX:%d maxPosY:%d\n", minPosX, minPosY, maxPosX, maxPosY);
			for(int y = minPosY; y <= maxPosY && !wordBreak; y++)
			{
				for(int x = minPosX; x <= maxPosX && !wordBreak; x++)
				{
					// is word into another ?
					tmpX = posX; tmpY = posY;
					emptyBreak = 1;
					for(int j = 0; j < len[i]; j++)
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
						for(int j = 0; j < len[i]; j++)
						{
							char gridVal = grid[gridLenX*tmpY+tmpX];
							if(gridVal == EMPTY || gridVal == list[i][j])
								ROT(rot,tmpX,tmpY)
							else
								emptyBreak = 0;
						}
						if(i == 2)
							printf("posX:%d posY:%d ", posX, posY);
						if(i == 2)
							printf("emptyBreak:%d\n", emptyBreak);
						// if word can be here, pass to next word
						if(emptyBreak)
						{
							// pass to next word
							wordBreak = 1;
							// and write it into grid
							tmpX = posX; tmpY = posY;
							printf("r:%d, x:%d, y:%d\n", rot, posX, posY);
							for(int j = 0; j < len[i]; j++)
							{
								grid[gridLenX*tmpY+tmpX] = list[i][j];
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
			minPosX = BTW(rot,len[i]-1,3,5);
			maxPosX = gridLenX - 1 - NEQ2(rot,len[i]-1,2,6); // size X
			minPosY = BTW(rot,len[i]-1,5,7);
			maxPosY = gridLenY - 1 - NEQ2(rot,len[i]-1,0,4); // size Y
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
					// MUST BE COMPLETED

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

	return 0;
}

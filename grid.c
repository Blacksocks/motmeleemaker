#include <stdio.h>

#include "grid.h"
#include "word.h"

void displayGrid(grid_t * grid)
{
	for(int j = 0; j < grid->d.h; j++)
	{
		for(int i = 0; i < grid->d.w; i++)
			for(int k = 0; k < nbOfBytesInChar(POS(grid, i, j).c[0]); k++)
				putchar(POS(grid, i, j).c[k]);
		printf("\n");
	}
}

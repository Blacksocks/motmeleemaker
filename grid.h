#ifndef _GRID_H_
#define _GRID_H_

#include "word.h"

#define EMPTY			'.'

typedef struct s_grid {
   char * 	g;  // grid array
   int 		lx; // grid width
   int 		ly; // grid height
   int		w;  // grid width into memory
} t_grid;

/* Generate a "mot melee" game from strings array
** grid: 			output grid
** list: 			main input, array of strings
** listLen: 		len of each string
** listLenLen: 		number of words
** return: does a problem occured ? (exemple: grid too small)
*/
int gridGenerator(t_grid * grid, char ** list, const int * len, const int listLen);

/* Fill grid with random letters
** grid:		grid where words must be inserted
** letters:		characters which could be used
** lettersLen:	lenght of letters array
*/
void fillGrid(t_grid * grid, char * letters, int letterLen);

/* Resize grid
** grid:			grid displayed
*/
void resizeGrid(t_grid * grid);

/* Calculate dimenstion of non empty window of grid
** grid:			input grid
** x1:				window X position
** y1:				window Y position
** x2:				window width + window X position
** y2:				window height + window Y positin
*/
void getGridSize(t_grid * grid, int * x1, int * y1, int * x2, int * y2);

/* Copy a grid into another
** grid1;			output grid
** grid2:			input grid
*/
void gridCopy(t_grid * grid1, const t_grid * grid2);

/* Grid printer function
** grid:			grid displayed
*/
void gridDisplay(t_grid * grid);

#endif // _GRID_H_
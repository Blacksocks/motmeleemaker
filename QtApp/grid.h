#ifndef GRID_H
#define GRID_H

#include "word.h"

#define POS(grid,x,y)	grid->g[grid->d.w * (y) + x]

typedef struct dim_s {
    int 		w;
    int 		h;
} dim_t;

typedef struct grid_s {
   char_t * 	g; // grid array
   dim_t		d;  // array dimensions
} grid_t;

/* Display grid
** grid:		grid we want to Display
*/
void displayGrid(grid_t * grid);

/* Create new grid from file (inputFileName) of words
** returns whether an error occured or not
*/
int createGrid();

#endif // GRID_H

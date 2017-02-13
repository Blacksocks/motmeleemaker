#ifndef _GRID_H_
#define _GRID_H_

#define EMPTY			'.'

/* Generate a "mot melee" game from strings array
** grid: 			output array of char
** gridLenX: 		grid width
** gridLenY: 		grid height
** list: 			main input, array of strings
** listLen: 		len of each string
** listLenLen: 		number of words
** return: does a problem occured ? (exemple: grid too small)
*/
int gridGenerator(char * grid, const int gridLenX, const int gridLenY, char ** list, const int * len, const int listLen);

/* Insert a word into a grid smartly
** grid:		grid here the ord must be insterted
** gridLenX:	width of the grid
** gridLenY:	height of the grid
** word:		current word
** wordLen:		lenght of the word
** return: insertion successful ?
*/
int insertWord(char * grid, int gridLenX, int gridLenY, char * word, int wordLen);

/* Fill grid with random letters
** grid:		grid here the ord must be insterted
** gridLenX:	width of the grid
** gridLenY:	height of the grid
** letters:		characters which could be used
** lettersLen:	lenght of letters array
*/
void fillGrid(char * grid, int gridLenX, int gridLenY, char * letters, int letterLen);

/* Resize grid
** grid:			grid displayed
** gridLenX: 		grid width
** gridLenY: 		grid height
*/
void resizeGrid(char * grid, int * gridLenX, int * gridLenY);

/* Calculate dimenstion of non empty window of grid
** grid:			grid displayed
** gridLenX: 		grid width
** gridLenY: 		grid height
** x1:				window X position
** y1:				window Y position
** x2:				window width + window X position
** y2:				window height + window Y positin
*/
void getGridSize(char * grid, int gridLenX, int gridLenY, int * x1, int * y1, int * x2, int * y2);

/* Copy a grid into another
** grid1;			output grid
** grid2:			input grid
** gridLenX: 		grid width
** gridLenY: 		grid height
*/
void gridCopy(char * grid1, const char * grid2, int gridLenX, int gridLenY);

/* Grid printer function
** grid:			grid displayed
** gridLenX: 		grid width
** gridLenY: 		grid height
*/
void gridDisplay(char * grid, int gridLenX, int gridLenY);

#endif // _GRID_H_

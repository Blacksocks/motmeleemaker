#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#include "grid.h"

/* Get dimensions of the content of file, i.e. nb of lines and cols of the first line
** f:			file to inspect
** dim:			dimensions of the file
*/
void getDimFile(FILE * f, dim_t * dim);

/* Get dimensions of the words of file, i.e. nb of cols of each line
** f:			file to inspect
** dim:			dimensions of the file
*/
void getWDimFile(FILE * f, int * dim);

/* Get values of the grid from a file
** f:			file to inspect
** grid:		grid to fill
*/
void getGrid(FILE * f, char_t * grid);

/* Get values of the words from a file
** f:			file to inspect
** words:			words array
*/
void getWords(FILE * f, word_t * words);

#endif // FILE_H

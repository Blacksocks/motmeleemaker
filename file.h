#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

/* Get number of lines of a file
** f:		file to inspect
*/
int getNbLines(FILE * f);

/* Get len of words contains into the file
** Works only for one word per line
** f:		file to inspect
** len:		array of word length
*/
void getWordsLen(FILE * f, int * len);

/* Copy words from file into an char * array
** f:		file to read
** list:	list of words
*/
void getWords(FILE * f, char ** list);

#endif // _FILE_H_

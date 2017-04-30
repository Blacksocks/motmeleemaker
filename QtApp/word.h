#ifndef WORD_H
#define WORD_H

#define CHARSIZE		(4)

typedef struct char_s {
    unsigned char c[CHARSIZE];
} char_t;

typedef struct word_s {
    char_t *	w; // string
    int			l; // length of the word
} word_t;

typedef struct words_s {
    word_t *    w; // words array
    int         l; // length of words list
} words_t;

/* Return number of bytes used to store a char in utf8
** val:			value to examine
*/
int nbOfBytesInChar(unsigned char val);

/* Display a words
** word:		words to print
*/
void printW(word_t * word);

/* Compare two string, a word_t and an unsigned char
** return 1 if strings are the same, 0 else
** word:		first string
** in:			second string
** inLen:		length of the second string
*/
int cmpWaUS(word_t * word, unsigned char * in, int inLen);

/* Get number of chars from unsigned char array
** array:		input array
** maxLen:		max length of input
*/
int getUCLen(unsigned char * array, int maxLen);

/* Get words from input file
** filename:    input file name
** returns whether an error occured or not
*/
int getWords(char * filename);

#endif // WORD_H

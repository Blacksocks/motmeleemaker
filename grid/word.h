#ifndef _WORD_H_
#define _WORD_H_

#define MAXLETLEN		(256)
#define CHARSIZE		(4)

typedef struct char_s {
	unsigned char c[CHARSIZE];
} char_t;

typedef struct word_s {
   char_t * 	w;   // word
   int 			len; // word length
} word_t;

/* Sort a list of string from longer to smaller
** list: 		list where strings are
** len: 		array which contains size of strings
** listLen: 	length of list array
*/
void sort(char_t ** list, int * len, const int listLen);

/* Get letters set from set for words
** list: 			main input, array of strings
** len:				len of each string
** listLen: 		number of words
** let:				array of letters
** letlen:			size of lettesr array
*/
void getLettersFromWords(char_t ** list, const int * len, const int listLen, char_t * let, int * letLen);

/* Compare two char_t
** return 1 if char_t are the same, else 0
** c1:				first char_t
** c2:				second char_t
*/
int cmpChar(const char_t * c1, const char_t * c2);

/* Write a char_t into another
** c1:				char to replace
** c2:				char to copy
*/
void setChar(char_t * c1, const char_t * c2);

#endif // _WORD_H_

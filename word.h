#ifndef _WORD_H_
#define _WORD_H_

#define MAXLETLEN		(256)

typedef struct s_word {
   char * 	w;   // word
   int 		len; // word length
} t_word;

/* Sort a list of string from longer to smaller
** list: 		list where strings are
** len: 		array which contains size of strings
** listLen: 	length of list array
*/
void sort(char ** list, int * len, const int listLen);

/* Get letters set from set for words
** list: 			main input, array of strings
** len:				len of each string
** listLen: 		number of words
** let:				array of letters
** letlen:			size of lettesr array
*/
void getLettersFromWords(char ** list, const int * len, const int listLen, char * let, int * letLen);

#endif // _WORD_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include "word.h"
#include "grid.h"
#include "file.h"

#define OUTFILE			"out.txt"
#define GRIDPATH		"/home/blacksocks/Documents/Programming/MotMeleeMaker/grid/main"
#define GRIDPRGM		"main"
#define MAXLEN			512

static char * argvChild[] = {GRIDPRGM, 0, OUTFILE, NULL};

int scan_line(unsigned char * buffer, int buffer_size)
{
	unsigned char * p = buffer;
	int count = 0;
	do
	{
		unsigned char c;
		int ret = scanf("%c", &c); // scan a single character
		if(ret <= 0)
			return 1;
		// break on end of line, string terminating NUL, or end of file
		if (c == '\r' || c == '\n' || c == 0)
		{
			*p = 0;
			break;
		}
		*p++ = c; // add the valid character into the buffer
	}
	while (count < buffer_size - 1);  // don't overrun the buffer
	// ensure the string is null terminated
	buffer[buffer_size - 1] = 0;
	return 0;
}

/* Check if an integer array contains an integer
** return 1 if yes, else 0
** array:		integer array
** len:			array length
** val:			value to find
*/
int contains(int * array, int len, int val)
{
	for(int i = 0; i < len; i++)
		if(array[i] == val)
			return 1;
	return 0;
}

/* Main function. Content of the game
** grid:		input grid
** words:		input words
** nbWords:		number of words
*/
void game(grid_t * grid, word_t * words, int nbWords)
{
	unsigned char in[MAXLEN]; // user input
	int inLen;
	int retry;
	int * found = malloc(sizeof(int) * nbWords);
	// initialise found array to -1
	for(int i = 0; i < nbWords; i++)
		found[i] = -1;
	for(int i = 0; i < nbWords; i++)
	{
		do
		{
			retry = 0;
			displayGrid(grid);
			printf("number of remaining words: %d\n", nbWords - i);
			inLen = scan_line(in, MAXLEN);
			if(inLen)
			{
				printf("[ERROR] Input error, try again\n");
				retry = 1;
				continue;
			}
			//inLen = scanf("[%s/n]", in);
			//in[MAXLEN - 1] = 0;
			// get number of chars into in
			inLen = getUCLen(in, MAXLEN);
			// check if this word exists into words array
			retry = 1;
			for(int j = 0; j < nbWords; j++)
				if(!contains(found, nbWords, j) && words[j].l == inLen)
					if(cmpWaUS(words+j, in, MAXLEN))
					{
						found[i] = j;
						retry = 0;
						break;
					}
			if(retry)
				printf("[INFO] Wrong answer, try again\n");
		}
		while(retry);
	}
	free(found);
	printf("Congratulations, you won !\n");
}

int main(int argc, char * argv[])
{
	if(argc < 2 || argc > 3)
	{
		printf("Usage: main fileAsk[, fileAns]\n"
		"Desc: This program will create a 'mot melee' grid from the first file\n"
		"      and user will must to find these words (or ones from second file) to win.\n"
		"  fileAsk: (string) text file with one word per line. Use to create grid.\n"
		"  fileAns: (strnig) file similar to the first. User must answser these words.\n");
		return 1;
	}

	// create grid using another program
	pid_t pid = fork();
	if(pid == EAGAIN || pid == ENOMEM || pid == ENOSYS)
	{
		printf("[ERROR] An error occured during fork\n");
		return 1;
	}
    if(pid == 0)
	{
		// child process
		argvChild[1] = argv[1];
        execv(GRIDPATH, argvChild);
        printf("[ERROR] An error occured during execv: %s\n", strerror(errno));
		return 1;
    }
    else
	{
		// pid != 0, parent process
		// wait for child to exit
		int status;
		if(waitpid(pid, &status, 0) == -1)
		{
			printf("[ERROR] An error occured dunring waitpid\n");
			return 1;
		}
        if(status)
		{
			printf("[ERROR] Child returned: %d\n", status);
			return 1;
		}
    }

	FILE * file = fopen(OUTFILE, "r");
	if(!file)
	{
		printf("[ERROR] Grid file \"%s\" error: %s\n", OUTFILE, strerror(errno));
		return 1;
	}
	dim_t g_dim;
	getDimFile(file, &g_dim);
	printf("dim: %d, %d\n", g_dim.w, g_dim.h);
	char_t * g_grid = malloc(sizeof(char_t) * g_dim.w * g_dim.h);
	getGrid(file, g_grid);
	grid_t grid = {g_grid, g_dim};

	// Get words array
	dim_t dim;
	file = fopen((argc == 3) ? argv[2] : argv[1], "r");
	if(!file)
	{
		printf("[ERROR] Grid file \"%s\" error: %s\n", argv[1], strerror(errno));
		return 1;
	}
	getDimFile(file, &dim);
	word_t * words = malloc(sizeof(word_t) * dim.h);
	int * wDim = malloc(sizeof(int) * dim.h);
	getWDimFile(file, wDim);
	for(int i = 0; i < dim.h; i++)
	{
		words[i].w = malloc(sizeof(char_t) * wDim[i]);
		words[i].l = wDim[i];
	}
	getWords(file, words);

	game(&grid, words, dim.h);

	printf("[INFO] Program ended successfully\n");
	return 0;
}

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

static char *argvChild[] = {GRIDPRGM, 0, OUTFILE, NULL};

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
	for(int i = 0; i < nbWords; i++)
	{
		do
		{
			retry = 0;
			displayGrid(grid);
			printf("number of remaining words: %d\n", nbWords - i);
			inLen = scanf("%s", in);
			if(inLen <= 0)
			{
				retry = 1;
				printf("[ERROR] Input error, try again\n");
				continue;
			}
			in[MAXLEN - 1] = 0;
			// get number of chars into in
			inLen = getUCLen(in, MAXLEN);
			// check if this word exists into words array
			retry = 1;
			for(int j = 0; j < nbWords; j++)
				if(words[j].l == inLen)
					if(cmpWaUS(words+j, in, MAXLEN))
					{
						retry = 0;
						break;
					}
			if(retry)
				printf("[INFO] Wrong answer, try again\n");
		}
		while(retry);
	}
	printf("Congratulations, you won !\n");
}

int main(int argc, char * argv[])
{
	if(argc < 2 || argc > 2)
	{
		printf("Usage: main filein\n"
		"  filein: (string) input text file with one word per line\n");
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
	file = fopen(argv[1], "r");
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

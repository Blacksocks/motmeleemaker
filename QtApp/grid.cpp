#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#include "grid.h"
#include "word.h"
#include "file.h"
#include "path.h"

extern grid_t * grid;
extern char * inputFileName;

void displayGrid(grid_t * grid)
{
    for(int j = 0; j < grid->d.h; j++)
    {
        for(int i = 0; i < grid->d.w; i++)
            for(int k = 0; k < nbOfBytesInChar(POS(grid, i, j).c[0]); k++)
                putchar(POS(grid, i, j).c[k]);
        printf("\n");
    }
}

/* Generate grid from another program
** prgm:        program path
** args:        program arguments
** returns whether an error occured or not
*/
int generateGrid(char * prgm, char * args[])
{
    pid_t pid = fork();
    if(pid == EAGAIN || pid == ENOMEM || pid == ENOSYS)
    {
        printf("[ERROR] An error occured during fork\n");
        return 1;
    }
    if(pid == 0)
    {
        // child process
        printf("%s\n", prgm);
        execv(prgm, args);
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
            printf("[ERROR] An error occured during waitpid\n");
            return 1;
        }
        if(status)
        {
            printf("[ERROR] Child returned: %d\n", status);
            return 1;
        }
    }
    return 0;
}

/* Load grid from file
** filename:    input file name
** returns whether an error occured or not
*/
int loadGrid(char * in)
{
    FILE * file = fopen(in, "r");
    if(!file)
    {
        printf("[ERROR] Grid file \"%s\" error: %s\n", in, strerror(errno));
        return 1;
    }
    dim_t g_dim;
    getDimFile(file, &g_dim);
    char_t * g_grid = new char_t[g_dim.w * g_dim.h];
    getGrid(file, g_grid);
    grid = new grid_t;
    grid->g = g_grid;
    grid->d = g_dim;
    return 0;
}

int createGrid()
{
    // create grid using another program
    char * argvChild[] = {GRIDPRGM, inputFileName, OUTFILE, NULL};
    if(generateGrid(GRIDPRGM, argvChild))
        return 1;
    printf("[INFO] Grid successfully produced\n");

    // Load grid
    if(loadGrid(OUTFILE))
        return 1;
    printf("[INFO] Grid successfully loaded\n");

    // Get words array
    if(getWords(TRADFILE))
        return 1;
    printf("[INFO] Translation words successfully loaded\n");
    return 0;
}

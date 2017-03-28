#include <QApplication>

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "mainwindow.h"
#include "word.h"
#include "grid.h"
#include "file.h"

#define PROJPATH        "/media/blacksocks/Data/blacksocks/Documents/Programming/MotMeleeMaker/"
#define OUTFILE			PROJPATH "out.txt"
#define INFILE          PROJPATH "in.txt"
#define TRADFILE        PROJPATH "fr.txt"
#define GRIDPATH		PROJPATH "grid/"
#define GRIDPRGM		GRIDPATH "main"

grid_t * grid;
words_t * words;

static char * argvChild[] = {GRIDPRGM, INFILE, OUTFILE, NULL};

int main(int argc, char *argv[])
{
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
        printf(GRIDPRGM "\n");
        execv(GRIDPRGM, argvChild);
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
    printf("[INFO] Grid successfully produced\n");

    // Load grid
    FILE * file = fopen(OUTFILE, "r");
    if(!file)
    {
        printf("[ERROR] Grid file \"%s\" error: %s\n", OUTFILE, strerror(errno));
        return 1;
    }
    dim_t g_dim;
    getDimFile(file, &g_dim);
    char_t * g_grid = new char_t[g_dim.w * g_dim.h];
    getGrid(file, g_grid);
    grid = new grid_t;
    grid->g = g_grid;
    grid->d = g_dim;
    printf("[INFO] Grid successfully loaded\n");

    // Get words array
    dim_t dim;
    file = fopen(TRADFILE, "r");
    if(!file)
    {
        printf("[ERROR] Traduction file \"%s\" error: %s\n", TRADFILE, strerror(errno));
        return 1;
    }
    getDimFile(file, &dim);
    word_t * wordArray = new word_t[dim.h];
    int * wDim = new int[dim.h];
    getWDimFile(file, wDim);
    for(int i = 0; i < dim.h; i++)
    {
        wordArray[i].w = new char_t[wDim[i]];
        wordArray[i].l = wDim[i];
    }
    getWords(file, wordArray);
    words = new words_t;
    words->w = wordArray;
    words->l = dim.h;

    // GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int ret = a.exec();

    // Clean
    delete[] g_grid;

    return ret;
}

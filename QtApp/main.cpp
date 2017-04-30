#include <QApplication>
#include <stdio.h>

#include "mainwindow.h"
#include "grid.h"
#include "path.h"

char * inputFileName = INFILE;
grid_t * grid;
words_t * words;

int main(int argc, char *argv[])
{
    // generate new grid from input file (inputFileName)
    // and update "grid" and "words" variables
    if(createGrid())
        return 1;

    // GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int ret = a.exec();
    return ret;
}

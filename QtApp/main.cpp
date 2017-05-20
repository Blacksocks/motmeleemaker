#include <QApplication>
#include <stdio.h>

#include "mainwindow.h"
#include "grid.h"
#include "path.h"

char * inputFileName = new char[128];
char * tradFileName = new char[128];
grid_t * grid;
words_t * outWords;
words_t * inWords;

int main(int argc, char *argv[])
{
    strcpy(inputFileName, INFILE);
    strcpy(tradFileName, TRADFILE);
    if(createGrid())
        return 1;

    // GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int ret = a.exec();
    return ret;
}

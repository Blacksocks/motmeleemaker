#include <QApplication>
#include <stdio.h>

#include "mainwindow.h"
#include "grid.h"
#include "path.h"

char * inputFileName = INFILE;
grid_t * grid;
words_t * outWords;
words_t * inWords;

int main(int argc, char *argv[])
{
    if(createGrid())
        return 1;

    // GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int ret = a.exec();
    return ret;
}

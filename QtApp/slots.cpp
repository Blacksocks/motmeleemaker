#include <stdio.h>

#include "mainwindow.h"
#include "grid.h"
#include "layout.h"

void MainWindow::slotBtnSubmit()
{
    QString input = getInputText();
    printf("[ACTION] submition - try:%s res:%s\n", qPrintable(input), showAnswer(input) ? "success" : "fail");
}

void MainWindow::slotBtnRestart()
{
    printf("[ACTION] restart grid\n");
    createGrid();
    updateGrid(getGridLayout());
}

void MainWindow::slotBtnAnswers()
{
    printf("[ACTION] display answers\n");
}

void MainWindow::slotBtnBrowse()
{
    printf("[ACTION] import input file\n");
}

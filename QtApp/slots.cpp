#include "mainwindow.h"

void MainWindow::slotBtnSubmit()
{
    QString input = getInputText();
    printf("try:%s res:%s\n", qPrintable(input), showAnswer(input) ? "success" : "fail");
}

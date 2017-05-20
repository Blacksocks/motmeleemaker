#include "mainwindow.h"

extern QList<QString *> input;
extern QList<QString *> answers;

void MainWindow::slotBtnSubmit()
{
    QString input = getInputText();
    printf("try:%s res:%s\n", qPrintable(input), showAnswer(input) ? "success" : "fail");
}

void MainWindow::slotTranslateBtn(int i)
{
    QLabel * label = getAnswerLabel(i);
    const char * in = input[i]->toUtf8().constData();
    const char * la = label->text().toUtf8().constData();
    if(strcmp(in, la))
        label->setText(input[i]->toUtf8().constData());
    else
        label->setText(answers[i]->toUtf8().constData());
}

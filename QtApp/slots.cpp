#include <stdio.h>
#include <QFileDialog>

#include "mainwindow.h"
#include "grid.h"
#include "layout.h"
#include "signals.h"

extern QList<QString *> input;
extern QList<QString *> answers;
extern char * inputFileName;
extern char * tradFileName;

void MainWindow::slotBtnSubmit()
{
    QString input = getInputText();
    QVBoxLayout * answersLayout = getAnswerLayout();
    int correct = 0;
    for(int i = 0; i < answers.size(); i++)
        if(answers.at(i)->compare(input) == 0)
        {
            answersLayout->itemAt(i)->widget()->show();
            correct = 1;
            break;
        }
    printf("[ACTION] submition - try:%s res:%s\n", qPrintable(input), correct ? "success" : "fail");
}

void MainWindow::slotBtnRestart()
{
    printf("[ACTION] restart grid\n");
    QVBoxLayout * answersLayout = getAnswerLayout();
    for(int i = 0; i < answers.size(); i++)
        answersLayout->itemAt(i)->widget()->hide();
    createGrid();
    updateGrid(getGridLayout());
}

void MainWindow::slotBtnAnswers()
{
    printf("[ACTION] display answers\n");
    QVBoxLayout * answersLayout = getAnswerLayout();
    for(int i = 0; i < answers.size(); i++)
        answersLayout->itemAt(i)->widget()->show();
}

void MainWindow::slotBtnBrowse()
{
    printf("[ACTION] import input file\n");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text (*.txt)"));
    printf("file choosed: %s\n", fileName.toUtf8().constData());
    strcpy(inputFileName, fileName.toUtf8().constData());
    strcpy(tradFileName, fileName.toUtf8().constData());
    int tradLen = strlen(tradFileName);
    tradFileName[tradLen - 3] = 't';
    tradFileName[tradLen - 2] = 'r';
    tradFileName[tradLen - 1] = 'a';
    tradFileName[tradLen] = 'd';
    tradFileName[tradLen + 1] = '\0';
    slotBtnRestart();
    updateAnswersLayout(getAnswerLayout());
    setInputWords();
    createSignals(this);
}

void MainWindow::slotTranslateBtn(int i)
{
    QLabel * label = getAnswerLabel(i);
    const char * in = input[i]->toUtf8().constData();
    const char * la = label->text().toUtf8().constData();
    printf("%d, %d\n", input.count(), answers.count());
    if(strcmp(in, la))
        label->setText(input[i]->toUtf8().constData());
    else
        label->setText(answers[i]->toUtf8().constData());
}

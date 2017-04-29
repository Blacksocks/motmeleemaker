#include <QLayout>
#include <QLineEdit>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "word.h"
#include "layout.h"
#include "signals.h"

using namespace std;

extern QList<QString *> answers;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(createLayout());

    createSignals(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton * MainWindow::getSubmitBtn()
{
    return (QPushButton *)((QHBoxLayout *)((QVBoxLayout *)((QVBoxLayout *)this->centralWidget()->layout()->itemAt(0))->itemAt(1))->itemAt(0))->itemAt(1)->widget();
}

QString MainWindow::getInputText()
{
    return ((QLineEdit *)((QHBoxLayout *)((QVBoxLayout *)((QVBoxLayout *)this->centralWidget()->layout()->itemAt(0))->itemAt(1))->itemAt(0))->itemAt(0)->widget())->text();
}

int MainWindow::showAnswer(QString label)
{
    QVBoxLayout * answersLayout = (QVBoxLayout *)this->centralWidget()->layout()->itemAt(1);
    for(int i = 0; i < answers.size(); i++)
        if(answers.at(i)->compare(label) == 0)
        {
            answersLayout->itemAt(i)->widget()->show();
            return 1;
        }
    return 0;
}

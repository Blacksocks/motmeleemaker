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

QPushButton * MainWindow::getRestartBtn()
{
    return (QPushButton *)((QHBoxLayout *)((QVBoxLayout *)((QVBoxLayout *)this->centralWidget()->layout()->itemAt(0))->itemAt(1))->itemAt(1))->itemAt(0)->widget();
}

QPushButton * MainWindow::getAnswersBtn()
{
    return (QPushButton *)((QHBoxLayout *)((QVBoxLayout *)((QVBoxLayout *)this->centralWidget()->layout()->itemAt(0))->itemAt(1))->itemAt(1))->itemAt(1)->widget();
}

QPushButton * MainWindow::getBrowseBtn()
{
    return (QPushButton *)((QHBoxLayout *)((QVBoxLayout *)((QVBoxLayout *)this->centralWidget()->layout()->itemAt(0))->itemAt(1))->itemAt(2))->itemAt(0)->widget();
}

QString MainWindow::getInputText()
{
    return ((QLineEdit *)((QHBoxLayout *)((QVBoxLayout *)((QVBoxLayout *)this->centralWidget()->layout()->itemAt(0))->itemAt(1))->itemAt(0))->itemAt(0)->widget())->text();
}

QVBoxLayout * MainWindow::getAnswerLayout()
{
    return (QVBoxLayout *)this->centralWidget()->layout()->itemAt(1);
}

QPushButton * MainWindow::getAnswerBtn(int i)
{
    QHBoxLayout * lay = (QHBoxLayout *)((QWidget *)getAnswerLayout()->itemAt(i)->widget())->layout();
    return (QPushButton *)(lay->itemAt(2)->widget());
}

QLabel * MainWindow::getAnswerLabel(int i)
{
    QHBoxLayout * lay = (QHBoxLayout *)((QWidget *)getAnswerLayout()->itemAt(i)->widget())->layout();
    return (QLabel *)(lay->itemAt(0)->widget());
}

QGridLayout * MainWindow::getGridLayout()
{
    return (QGridLayout *)((QVBoxLayout *)this->centralWidget()->layout()->itemAt(0))->itemAt(0)->layout();
}

int MainWindow::showAnswer(QString label)
{
    QVBoxLayout * answersLayout = getAnswerLayout();
    for(int i = 0; i < answers.size(); i++)
        if(answers.at(i)->compare(label) == 0)
        {
            answersLayout->itemAt(i)->widget()->show();
            return 1;
        }
    return 0;
}

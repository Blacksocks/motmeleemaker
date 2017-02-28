#include <QLayout>
#include <QLabel>
#include <QTextCodec>
#include <QPushButton>
#include <QLineEdit>
#include <list>
#include <stdio.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include "word.h"

#define GRID_BOX_WIDTH                  22
#define GRID_BOX_HEIGHT                 26
#define ANSWER_BTN_WIDTH                70
#define ANSWER_BTN_HEIGHT               26

extern grid_t * grid;
extern words_t * words;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int gridW = grid->d.w;
    int gridH = grid->d.h;

    // set buttons layout
    QVBoxLayout * btnLayout = new QVBoxLayout;
    QHBoxLayout * btn1Layout = new QHBoxLayout;
    QHBoxLayout * btn2Layout = new QHBoxLayout;
    QHBoxLayout * btn3Layout = new QHBoxLayout;
    QLineEdit * textInput = new QLineEdit;
    QPushButton * btnSubmit = new QPushButton(">");
    btn1Layout->addWidget(textInput);
    btn1Layout->addWidget(btnSubmit);
    QPushButton * btnRestart = new QPushButton("Restart");
    QPushButton * btnAnswers = new QPushButton("Answers");
    btn2Layout->addWidget(btnRestart);
    btn2Layout->addWidget(btnAnswers);
    QPushButton * btnFileIn = new QPushButton("Browse");
    btn3Layout->addWidget(btnFileIn);
    btnLayout->addLayout(btn1Layout);
    btnLayout->addLayout(btn2Layout);
    btnLayout->addLayout(btn3Layout);

    // set grid layout
    QTextCodec * codec = QTextCodec::codecForName("UTF-8");
    QGridLayout * gridLayout = new QGridLayout;
    for(int j = 0; j < gridH; j++)
        for(int i = 0; i < gridW; i++)
        {
            int idx = gridW*j+i;
            QLabel * label = new QLabel(codec->toUnicode((char*)grid->g[idx].c, nbOfBytesInChar(grid->g[idx].c[0])));
            label->setFixedSize(GRID_BOX_WIDTH, GRID_BOX_HEIGHT);
            gridLayout->addWidget(label, i, j);
        }

    // set anwers layout
    QVBoxLayout * answersLayout = new QVBoxLayout;
    list<QHBoxLayout *> answers = list<QHBoxLayout*>();
    for(int i = 0; i < words->l; i++)
    {
        QHBoxLayout * answerLayout = new QHBoxLayout;
        QString str = QString("");
        for(int j = 0; j < words->w[i].l; j++)
            str.append(codec->toUnicode((char*)words->w[i].w[j].c, nbOfBytesInChar(words->w[i].w[j].c[0])));
        QLabel * answerText = new QLabel(str);
        answerText->setFixedHeight(ANSWER_BTN_HEIGHT);
        QPushButton * answerBtn = new QPushButton("Translate");
        answerBtn->setFixedSize(ANSWER_BTN_WIDTH, ANSWER_BTN_HEIGHT);
        answerLayout->addWidget(answerText);
        answerLayout->addStretch();
        answerLayout->addWidget(answerBtn);
        answers.push_back(answerLayout);
    }
    for (list<QHBoxLayout *>::const_iterator it = answers.begin(); it != answers.end(); ++it)
        answersLayout->addLayout(*it);
    answersLayout->addStretch();

    // set layout
    QHBoxLayout * layout = new QHBoxLayout;
    QVBoxLayout * leftLayout = new QVBoxLayout;
    leftLayout->addLayout(gridLayout);
    leftLayout->addLayout(btnLayout);
    leftLayout->addStretch();
    layout->addLayout(leftLayout);
    layout->addLayout(answersLayout);
    layout->setStretch(0, 0);
    layout->setStretch(1, 1000);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

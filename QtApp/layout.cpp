#include <QLineEdit>
#include <QPushButton>
#include <QTextCodec>
#include <QLabel>
#include <list>

#include "layout.h"
#include "grid.h"

extern grid_t * grid;
extern words_t * inWords;
extern words_t * outWords;
QList<QString *> input;
QList<QString *> answers;

QHBoxLayout * createLayout()
{
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
    for(int i = 0; i < outWords->l; i++)
    {
        QHBoxLayout * answerLayout = new QHBoxLayout;
        QString * str = new QString("");
        for(int j = 0; j < outWords->w[i].l; j++)
            str->append(codec->toUnicode((char*)outWords->w[i].w[j].c, nbOfBytesInChar(outWords->w[i].w[j].c[0])));
        QLabel * answerText = new QLabel(*str);
        answerText->setFixedHeight(ANSWER_BTN_HEIGHT);
        answers.push_back(str);
        QPushButton * answerBtn = new QPushButton("Translate");
        answerBtn->setFixedSize(ANSWER_BTN_WIDTH, ANSWER_BTN_HEIGHT);
        answerLayout->addWidget(answerText);
        answerLayout->addStretch();
        answerLayout->addWidget(answerBtn);
        QWidget * answer = new QWidget();
        answer->setLayout(answerLayout);
        answer->hide();
        answerLayout->setContentsMargins(0, 0, 0, 0);
        answersLayout->addWidget(answer);
    }
    answersLayout->addStretch();

    // set input words list
    for(int i = 0; i < inWords->l; i++)
    {
        QString * str = new QString("");
        for(int j = 0; j < inWords->w[i].l; j++)
            str->append(codec->toUnicode((char*)inWords->w[i].w[j].c, nbOfBytesInChar(inWords->w[i].w[j].c[0])));
        input.push_back(str);
    }

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

    return layout;
}

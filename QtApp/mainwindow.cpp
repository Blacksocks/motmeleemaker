#include <QLayout>
#include <QLabel>
#include <QTextCodec>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"

extern grid_t * grid;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int gridW = grid->d.w;
    int gridH = grid->d.h;

    QLabel ** boxes = new QLabel * [gridH * gridW];

    // set buttons layout
    QVBoxLayout * btnLayout = new QVBoxLayout;

    // set grid layout
    QGridLayout * gridLayout = new QGridLayout;
    // set label content
    QTextCodec * codec = QTextCodec::codecForName("UTF-8");
    for(int i = 0; i < gridH * gridW; i++)
        boxes[i] = new QLabel(codec->toUnicode((char*)grid->g[i].c, nbOfBytesInChar(grid->g[i].c[0])));
    // set layout
    for(int j = 0; j < gridH; j++)
        for(int i = 0; i < gridW; i++)
            gridLayout->addWidget(boxes[gridW*j+i], i, j);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(gridLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

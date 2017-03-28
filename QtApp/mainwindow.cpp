#include <QLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "word.h"
#include "layout.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(createLayout());
}

//connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

MainWindow::~MainWindow()
{
    delete ui;
}

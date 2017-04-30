#include <QPushButton>

#include "signals.h"

void createSignals(MainWindow * mainwindow)
{
    QObject::connect(mainwindow->getSubmitBtn(), SIGNAL(clicked()), mainwindow, SLOT(slotBtnSubmit()));
    QObject::connect(mainwindow->getRestartBtn(), SIGNAL(clicked()), mainwindow, SLOT(slotBtnRestart()));
    QObject::connect(mainwindow->getAnswersBtn(), SIGNAL(clicked()), mainwindow, SLOT(slotBtnAnswers()));
    QObject::connect(mainwindow->getBrowseBtn(), SIGNAL(clicked()), mainwindow, SLOT(slotBtnBrowse()));
}

#include <QPushButton>

#include "signals.h"

void createSignals(MainWindow * mainwindow)
{
    //printf("%s\n", btnSubmit->text().toLatin1().constData());
    QObject::connect(mainwindow->getSubmitBtn(), SIGNAL(clicked()), mainwindow, SLOT(slotBtnSubmit()));
}

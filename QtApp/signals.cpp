#include <QPushButton>
#include <QSignalMapper>

#include "signals.h"

void createSignals(MainWindow * mainwindow)
{
    // submit signal
    QObject::connect(mainwindow->getSubmitBtn(), SIGNAL(clicked()), mainwindow, SLOT(slotBtnSubmit()));
    // translate signals
    QSignalMapper * mapper = new QSignalMapper(mainwindow);
    QVBoxLayout * answersLayout = (QVBoxLayout *)mainwindow->centralWidget()->layout()->itemAt(1);
    for(int i = 0; i < answersLayout->count() - 1; i++){
        QHBoxLayout * lay = (QHBoxLayout *)((QWidget *)answersLayout->itemAt(i)->widget())->layout();
        QPushButton * btn = (QPushButton *)(lay->itemAt(2)->widget());
        QObject::connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(btn, i);
    }
    QObject::connect(mapper, SIGNAL(mapped(int)), mainwindow, SLOT(slotTranslateBtn(int)));
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit        MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *   getSubmitBtn();
    QString         getInputText();
    QVBoxLayout *   getAnswerLayout();
    QPushButton *   getAnswerBtn(int i);
    QLabel *        getAnswerLabel(int i);
    int             showAnswer(QString label);

private:
    Ui::MainWindow *ui;

private slots:
    void            slotBtnSubmit();
    void            slotTranslateBtn(int i);
};

#endif // MAINWINDOW_H

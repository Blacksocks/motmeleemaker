#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton * getSubmitBtn();
    QPushButton * getRestartBtn();
    QPushButton * getAnswersBtn();
    QPushButton * getBrowseBtn();
    QGridLayout * getGridLayout();
    QString getInputText();
    int showAnswer(QString label);

private:
    Ui::MainWindow *ui;

private slots:
    void slotBtnSubmit();
    void slotBtnRestart();
    void slotBtnAnswers();
    void slotBtnBrowse();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
    QString getInputText();
    int showAnswer(QString label);

private:
    Ui::MainWindow *ui;

private slots:
    void slotBtnSubmit();
};

#endif // MAINWINDOW_H

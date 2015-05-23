#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mywindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openNewWindow();

private slots:
    void on_pushButton_submit_clicked();

private:
    Ui::MainWindow *ui;
    myWindow *mMyNewWindow;
};

#endif // MAINWINDOW_H

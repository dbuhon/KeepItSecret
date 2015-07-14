#ifndef NEWACCOUNTWINDOW_H
#define NEWACCOUNTWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewAccountWindow;
}

class NewAccountWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAccountWindow(QWidget *parent = 0);
    ~NewAccountWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewAccountWindow *ui;
};

#endif // NEWACCOUNTWINDOW_H

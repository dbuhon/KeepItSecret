#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newaccountwindow.h"
#include "contactswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openNewAccountView();
    void openContactsView();

private slots:
    void on_pushButton_submit_clicked();
    void on_pushButton_newAccount_clicked();

private:
    Ui::MainWindow *ui;
    NewAccountWindow *newAccountWindow;
    ContactsWindow *contactsWindow;
};

#endif // MAINWINDOW_H

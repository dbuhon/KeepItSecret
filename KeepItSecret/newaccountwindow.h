#ifndef NEWACCOUNTWINDOW_H
#define NEWACCOUNTWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class NewAccountWindow;
}

class NewAccountWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAccountWindow(QWidget *parent = 0);
    ~NewAccountWindow();
    void setClient(Client *_client);

private slots:
    void on_pushButton_clicked();
    void adduser(bool isAdded);

private:
    Ui::NewAccountWindow *ui;
    Client *client;
};

#endif // NEWACCOUNTWINDOW_H
